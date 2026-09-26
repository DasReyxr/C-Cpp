"""
Newton interpolation checker for STM32 validation.

This script mirrors the C implementation in NewtonRapson.c:
- diferencias_divididas
- evalPol (Newton nested form)

It also computes an independent Lagrange interpolation value as reference,
so you can verify that your embedded implementation is correct.
"""

from __future__ import annotations

import math
from typing import Iterable, List, Sequence


def divided_differences(x_nodes: Sequence[float], y_nodes: Sequence[float]) -> List[float]:
    """Equivalent to diferencias_divididas(poli p) in C."""
    n = len(x_nodes)
    if n != len(y_nodes):
        raise ValueError("x_nodes and y_nodes must have the same length")
    if n == 0:
        raise ValueError("At least one node is required")

    a = list(y_nodes)

    for j in range(1, n):
        for i in range(n - 1, j - 1, -1):
            den = x_nodes[i] - x_nodes[i - j]
            if den == 0:
                raise ZeroDivisionError("Repeated x value found; interpolation is undefined")
            a[i] = (a[i] - a[i - 1]) / den

    return a


def newton_eval(x_nodes: Sequence[float], a: Sequence[float], x: float) -> float:
    """Equivalent to evalPol(float x, poli p, float *a) in C."""
    n = len(x_nodes)
    if len(a) != n:
        raise ValueError("Length of coefficients must match number of nodes")

    y = a[0]
    prod = 1.0
    for i in range(1, n):
        prod *= (x - x_nodes[i - 1])
        y += a[i] * prod
    return y


def lagrange_eval(x_nodes: Sequence[float], y_nodes: Sequence[float], x: float) -> float:
    """Independent reference method to validate Newton result."""
    n = len(x_nodes)
    total = 0.0

    for i in range(n):
        term = y_nodes[i]
        for j in range(n):
            if i == j:
                continue
            den = x_nodes[i] - x_nodes[j]
            if den == 0:
                raise ZeroDivisionError("Repeated x value found; interpolation is undefined")
            term *= (x - x_nodes[j]) / den
        total += term

    return total


def max_abs_diff(a: Iterable[float], b: Iterable[float]) -> float:
    return max(abs(x - y) for x, y in zip(a, b))


def rlc_response(t: float, wn: float, zeta: float) -> float:
    """Match the STM32 H(t, wn, zeta) implementation."""
    if zeta >= 1.0:
        return 0.0

    omega_d = (1.0 - zeta * zeta) ** 0.5
    return wn * math.exp(-zeta * wn * t) * math.sin(wn * omega_d * t) / omega_d


def generate_nodes_from_rlc(
    n: int,
    l_henry: float,
    c_farads: float,
    zeta: float,
    step: float = 0.01,
) -> tuple[list[float], list[float], float]:
    """Generate the same node set used by the embedded code."""
    if n < 2:
        raise ValueError("n must be at least 2")

    wn = 1.0 / ((l_henry * c_farads) ** 0.5)
    x_nodes = [step * (i + 1) for i in range(n)]
    y_nodes = [rlc_response(t, wn, zeta) for t in x_nodes]
    return x_nodes, y_nodes, wn


def run_check(
    x_nodes: Sequence[float],
    y_nodes: Sequence[float],
    x_eval: float,
    mcu_coeffs: Sequence[float] | None = None,
    mcu_y_eval: float | None = None,
) -> None:
    print("=" * 70)
    print("NEWTON INTERPOLATION CHECKER")
    print("=" * 70)

    coeffs_py = divided_differences(x_nodes, y_nodes)
    y_newton_py = newton_eval(x_nodes, coeffs_py, x_eval)
    y_lagrange_ref = lagrange_eval(x_nodes, y_nodes, x_eval)

    print(f"Nodes (n): {len(x_nodes)}")
    print(f"x_eval   : {x_eval:.8f}")
    print("\nPython Newton coefficients:")
    for i, c in enumerate(coeffs_py):
        print(f"a[{i}] = {c:.10f}")

    print("\nEvaluation:")
    print(f"Newton (Python)   = {y_newton_py:.10f}")
    print(f"Lagrange (ref)    = {y_lagrange_ref:.10f}")
    print(f"|diff|            = {abs(y_newton_py - y_lagrange_ref):.3e}")

    if mcu_coeffs is not None:
        if len(mcu_coeffs) != len(coeffs_py):
            print("\n[MCU CHECK] coefficient count mismatch")
            print(f"Python count = {len(coeffs_py)}, MCU count = {len(mcu_coeffs)}")
        else:
            coef_err = max_abs_diff(coeffs_py, mcu_coeffs)
            print("\n[MCU CHECK] coefficients")
            print(f"max |a_py - a_mcu| = {coef_err:.3e}")

    if mcu_y_eval is not None:
        print("\n[MCU CHECK] evaluation")
        print(f"y_mcu             = {mcu_y_eval:.10f}")
        print(f"|y_py - y_mcu|    = {abs(y_newton_py - mcu_y_eval):.3e}")

    print("\nStatus:")
    if abs(y_newton_py - y_lagrange_ref) < 1e-7:
        print("PASS: Python Newton matches reference.")
    else:
        print("WARN: Python Newton differs from reference; check data ordering.")


if __name__ == "__main__":
    # Match the STM32 code defaults.
    # For degree 10, use 11 nodes.
    n = 11
    l_henry = 2
    c_farads = 27e-6
    zeta = 0.57
    x_eval = 0.075

    x_nodes, y_nodes, wn = generate_nodes_from_rlc(n, l_henry, c_farads, zeta)

    print(f"Generated nodes from RLC model:")
    print(f"  L = {l_henry} H")
    print(f"  C = {c_farads} F")
    print(f"  zeta = {zeta}")
    print(f"  wn = {wn:.10f}")
    print()

    # Optional: paste values printed by your STM32 here.
    mcu_coeffs = None
    mcu_y_eval = None

    run_check(x_nodes, y_nodes, x_eval, mcu_coeffs=mcu_coeffs, mcu_y_eval=mcu_y_eval)
