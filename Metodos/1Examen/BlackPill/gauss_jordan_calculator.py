"""
Gauss-Jordan Calculator for Resistive Circuit Verification
Author: Orlando Reyes
Date: March 6, 2026

This script solves the same 6x6 system as the STM32 code to verify calculations.
Circuit: 6 resistors, 6 currents using Kirchhoff's laws
"""

import numpy as np

def solve_resistive_circuit(R):
    """
    Solve the resistive circuit with given resistor values.
    
    Parameters:
    R: list/array of 6 resistor values [R1, R2, R3, R4, R5, R6]
    
    Returns:
    currents: array of 6 current values [I1, I2, I3, I4, I5, I6]
    """
    
    # Build the coefficient matrix (6x6)
    matrix = np.array([
        [R[0],  0,     R[5],  0,     0,     R[4]],  # KVL equation 1
        [0,     R[1],  R[5],  R[2],  R[3],  0   ],  # KVL equation 2
        [1,    -1,    -1,     0,     0,     0   ],  # KCL equation 1
        [0,     1,     0,    -1,     0,     0   ],  # KCL equation 2
        [0,     0,     0,     1,    -1,     0   ],  # KCL equation 3
        [0,     0,     1,     0,     1,    -1   ]   # KCL equation 4
    ], dtype=float)
    
    # Build the results vector
    vector = np.array([200, 0, 0, 0, 0, 0], dtype=float)
    
    print("=" * 60)
    print("RESISTIVE CIRCUIT SOLVER - Gauss-Jordan Method")
    print("=" * 60)
    print(f"\nResistor Values (Ohms):")
    for i, r in enumerate(R):
        print(f"  R{i+1} = {r:.2f} Ω")
    
    print(f"\nCoefficient Matrix A:")
    print(matrix)
    print(f"\nResults Vector b:")
    print(vector)
    
    # Solve using numpy (equivalent to Gauss-Jordan elimination)
    try:
        currents = np.linalg.solve(matrix, vector)
        
        print("\n" + "=" * 60)
        print("SOLUTION - Circuit Currents:")
        print("=" * 60)
        for i, current in enumerate(currents):
            print(f"  I{i+1} = {current:.6f} A")
        
        # Verify the solution
        print("\n" + "=" * 60)
        print("VERIFICATION:")
        print("=" * 60)
        residual = np.dot(matrix, currents) - vector
        print(f"Residual (A·x - b): {residual}")
        print(f"Max error: {np.max(np.abs(residual)):.2e}")
        
        if np.max(np.abs(residual)) < 1e-10:
            print("✓ Solution is correct!")
        else:
            print("⚠ Warning: Solution may have errors")
        
        return currents
        
    except np.linalg.LinAlgError:
        print("\n❌ ERROR: Matrix is singular (no unique solution exists)")
        return None


def gauss_jordan_manual(A, b):
    """
    Manual Gauss-Jordan elimination implementation for verification.
    Mimics the C implementation exactly.
    """
    n = len(b)
    # Create augmented matrix
    aug = np.column_stack((A.copy(), b.copy()))
    
    print("\n" + "=" * 60)
    print("MANUAL GAUSS-JORDAN ELIMINATION STEPS:")
    print("=" * 60)
    
    for i in range(n):
        # Pivot element
        diag = aug[i, i]
        if abs(diag) < 1e-10:
            print(f"⚠ Warning: Very small pivot at row {i+1}")
            return None
        
        # Normalize row i
        aug[i, :] = aug[i, :] / diag
        print(f"\nStep {i+1}: Normalize row {i+1}")
        print(aug)
        
        # Eliminate column i in all other rows
        for j in range(n):
            if j != i:
                factor = aug[j, i]
                aug[j, :] = aug[j, :] - factor * aug[i, :]
        
        print(f"Step {i+1}: Eliminate column {i+1}")
        print(aug)
    
    # Extract solution from last column
    solution = aug[:, -1]
    
    print("\n" + "=" * 60)
    print("MANUAL GAUSS-JORDAN RESULT:")
    print("=" * 60)
    for i, val in enumerate(solution):
        print(f"  I{i+1} = {val:.6f} A")
    
    return solution


if __name__ == "__main__":
    # Example resistor values (in Ohms)
    # You can change these values to match your test cases
    
    print("\n" + "=" * 60)
    print("Enter resistor values (or press Enter for default values)")
    print("=" * 60)
    
    try:
        R1 = float(input("R1 (Ω) [default 100]: ") or 100)
        R2 = float(input("R2 (Ω) [default 200]: ") or 200)
        R3 = float(input("R3 (Ω) [default 300]: ") or 300)
        R4 = float(input("R4 (Ω) [default 400]: ") or 400)
        R5 = float(input("R5 (Ω) [default 500]: ") or 500)
        R6 = float(input("R6 (Ω) [default 600]: ") or 600)
        
        R = [R1, R2, R3, R4, R5, R6]
        
    except ValueError:
        print("Invalid input, using default values")
        R = [100, 200, 300, 400, 500, 600]
    
    # Solve using numpy
    print("\n" + "#" * 60)
    print("METHOD 1: NumPy Linear Solver (optimized)")
    print("#" * 60)
    currents_numpy = solve_resistive_circuit(R)
    
    # Solve using manual Gauss-Jordan
    print("\n" + "#" * 60)
    print("METHOD 2: Manual Gauss-Jordan (matches C implementation)")
    print("#" * 60)
    
    matrix = np.array([
        [R[0],  0,     R[5],  0,     0,     R[4]],
        [0,     R[1],  R[5],  R[2],  R[3],  0   ],
        [1,    -1,    -1,     0,     0,     0   ],
        [0,     1,     0,    -1,     0,     0   ],
        [0,     0,     0,     1,    -1,     0   ],
        [0,     0,     1,     0,     1,    -1   ]
    ], dtype=float)
    
    vector = np.array([200, 0, 0, 0, 0, 0], dtype=float)
    
    currents_manual = gauss_jordan_manual(matrix, vector)
    
    # Compare results
    if currents_numpy is not None and currents_manual is not None:
        print("\n" + "=" * 60)
        print("COMPARISON:")
        print("=" * 60)
        print(f"{'Current':<10} {'NumPy':<15} {'Manual':<15} {'Difference':<15}")
        print("-" * 60)
        for i in range(6):
            diff = abs(currents_numpy[i] - currents_manual[i])
            print(f"I{i+1:<9} {currents_numpy[i]:<15.6f} {currents_manual[i]:<15.6f} {diff:<15.2e}")
    
    print("\n" + "=" * 60)
    print("Use these values to verify your STM32 output!")
    print("=" * 60)
