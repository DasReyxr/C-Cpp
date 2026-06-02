
"""
Newton-Raphson Calculator for RLC Circuit Verification
Author: Orlando Reyes
Date: March 6, 2026

This script solves the same RLC differential equation as the STM32 code.
Finds resistance R such that: exp(-0.5*R*t/L) * cos(omega*t) = q
where omega = sqrt(1/(L*C) - R^2/(4*L^2))
L 10
C 0.0002
t 0.01
q 0.05
Intervalos
"""
4
import numpy as np
import math

def f(R, L, C, t, q):
    """
    RLC circuit function: exp(-0.5*R*t/L) * cos(omega*t) - q
    
    Parameters:
    R: Resistance (variable to solve for)
    L: Inductance (Henry)
    C: Capacitance (Farad)
    t: Time (seconds)
    q: Target charge/voltage
    
    Returns:
    Function value
    """
    omega = math.sqrt(1.0/(L*C) - (R*R)/(4.0*L*L))
    expo = math.exp((-0.5*R*t)/L)
    return expo * math.cos(omega*t) - q


def df(R, L, C, t):
    """
    Derivative of f with respect to R
    
    Returns:
    df/dR
    """
    omega = math.sqrt(1.0/(L*C) - (R*R)/(4.0*L*L))
    expo = math.exp((-0.5*R*t)/L)
    
    # df/dR = expo * [-(t/(2L))*cos(omega*t) + (R*t/(4*L^2*omega))*sin(omega*t)]
    result = expo * (
        -(t/(2.0*L))*math.cos(omega*t) +
        (R*t/(4.0*L*L*omega))*math.sin(omega*t)
    )
    return result


def newton_raphson(L, C, t, q, x0=0.5, max_iter=50, precision=0.0001):
    """
    Newton-Raphson method to find R
    
    Parameters:
    L: Inductance (H)
    C: Capacitance (F)
    t: Time (s)
    q: Target value
    x0: Initial guess for R
    max_iter: Maximum iterations
    precision: Convergence tolerance
    
    Returns:
    result: Dictionary with solution details
    """
    x_prev = x0
    iteration = 0
    
    print("=" * 80)
    print("NEWTON-RAPHSON METHOD - RLC CIRCUIT")
    print("=" * 80)
    print(f"\nCircuit Parameters:")
    print(f"  L (Inductance) = {L} H")
    print(f"  C (Capacitance) = {C} F")
    print(f"  t (Time) = {t} s")
    print(f"  q (Target value) = {q}")
    print(f"\nNumerical Parameters:")
    print(f"  Initial guess (x0) = {x0}")
    print(f"  Max iterations = {max_iter}")
    print(f"  Precision = {precision}")
    
    print("\n" + "-" * 80)
    print(f"{'Iter':<6} {'R':<15} {'f(R)':<15} {'f\'(R)':<15} {'Error (%)':<15}")
    print("-" * 80)
    
    while iteration < max_iter:
        fx = f(x_prev, L, C, t, q)
        dfx = df(x_prev, L, C, t)
        
        # Check for zero derivative
        if abs(dfx) < 1e-10:
            print(f"\n⚠ Warning: Derivative too small at iteration {iteration}")
            return {
                'value': x_prev,
                'error': None,
                'iterations': iteration,
                'success': False,
                'message': 'Zero derivative encountered'
            }
        
        # Newton-Raphson formula
        x_next = x_prev - fx / dfx
        
        # Calculate relative error
        if abs(x_next) > 1e-10:
            error = abs((x_next - x_prev) / x_next) * 100
        else:
            error = abs(x_next - x_prev) * 100
        
        print(f"{iteration:<6} {x_prev:<15.6f} {fx:<15.6e} {dfx:<15.6e} {error:<15.6f}")
        
        # Check convergence
        if abs(fx) < precision:
            print("-" * 80)
            print(f"\n✓ Converged after {iteration} iterations!")
            print(f"  R = {x_prev:.6f} Ω")
            print(f"  f(R) = {fx:.6e}")
            print(f"  Error = {error:.6f}%")
            
            return {
                'value': x_prev,
                'error': error,
                'iterations': iteration,
                'success': True,
                'message': 'Converged successfully'
            }
        
        x_prev = x_next
        iteration += 1
    
    # Max iterations reached
    print("-" * 80)
    print(f"\n⚠ Maximum iterations ({max_iter}) reached without convergence")
    print(f"  Best R = {x_prev:.6f} Ω")
    print(f"  f(R) = {f(x_prev, L, C, t, q):.6e}")
    
    return {
        'value': x_prev,
        'error': None,
        'iterations': iteration,
        'success': False,
        'message': 'Max iterations reached'
    }


def verify_solution(R, L, C, t, q):
    """
    Verify the solution by checking if f(R) ≈ 0
    """
    result = f(R, L, C, t, q)
    
    print("\n" + "=" * 80)
    print("VERIFICATION:")
    print("=" * 80)
    print(f"f({R:.6f}) = {result:.6e}")
    
    omega = math.sqrt(1.0/(L*C) - (R*R)/(4.0*L*L))
    damping_factor = math.exp((-0.5*R*t)/L)
    oscillation = math.cos(omega*t)
    
    print(f"\nBreakdown:")
    print(f"  ω (angular frequency) = {omega:.6f} rad/s")
    print(f"  Damping factor e^(-Rt/2L) = {damping_factor:.6f}")
    print(f"  Oscillation cos(ωt) = {oscillation:.6f}")
    print(f"  Product = {damping_factor * oscillation:.6f}")
    print(f"  Target q = {q:.6f}")
    print(f"  Difference = {abs(damping_factor * oscillation - q):.6e}")
    
    if abs(result) < 1e-4:
        print("\n✓ Solution verified!")
    else:
        print("\n⚠ Solution may need more iterations")


if __name__ == "__main__":
    print("\n" + "=" * 80)
    print("RLC CIRCUIT SOLVER - Newton-Raphson Method")
    print("=" * 80)
    print("\nEnter circuit parameters (or press Enter for default values):")
    
    try:
        L = float(input("L - Inductance in H [default 0.1]: ") or 0.1)
        C = float(input("C - Capacitance in F [default 0.001]: ") or 0.001)
        t = float(input("t - Time in s [default 0.05]: ") or 0.05)
        q = float(input("q - Target value [default 0.8]: ") or 0.8)
        x0 = float(input("x0 - Initial guess for R [default 0.5]: ") or 0.5)
        max_it = int(input("Max iterations [default 50]: ") or 50)
        precision = float(input("Precision [default 0.0001]: ") or 0.0001)
        
    except ValueError:
        print("Invalid input, using default values")
        L = 0.1
        C = 0.001
        t = 0.05
        q = 0.8
        x0 = 0.5
        max_it = 50
        precision = 0.0001
    
    # Solve using Newton-Raphson
    result = newton_raphson(L, C, t, q, x0, max_it, precision)
    
    # Verify solution
    if result['success']:
        verify_solution(result['value'], L, C, t, q)
    
    print("\n" + "=" * 80)
    print("Summary:")
    print("=" * 80)
    print(f"  R = {result['value']:.6f} Ω")
    print(f"  Iterations = {result['iterations']}")
    print(f"  Status = {result['message']}")
    if result['error'] is not None:
        print(f"  Final Error = {result['error']:.6f}%")
    
    print("\n" + "=" * 80)
    print("Use this value to verify your STM32 output!")
    print("=" * 80)
