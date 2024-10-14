#!/bin/bash

# Path to the Python script
PYTHON_SCRIPT="polynomial_solver.py"  # replace with the actual filename

# Valid test cases
valid_test_cases=(
    # Normal case: Quadratic equation with real roots
    '5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0'  # Expected: Two real roots

    # Normal case: Linear equation
    '5 * X^0 + 4 * X^1 = 4 * X^0'  # Expected: One real root

    # Edge case: Zero polynomial
    '0 * X^2 + 0 * X^1 + 0 * X^0 = 0'  # Expected: Infinite solutions

    # Edge case: No solution
    '4 * X^0 = 5 * X^0'  # Expected: No solution

    # Edge case: Quadratic equation with complex roots
    '1 * X^2 + 0 * X^1 + 1 * X^0 = 0'  # Expected: Two complex roots

    # Edge case: Linear equation with zero coefficient
    '0 * X^1 + 0 * X^0 = 5 * X^0'  # Expected: No solution

    # Edge case: Same term on both sides
    '42 * X^0 = 42 * X^0'  # Expected: Infinite solutions

    # Edge case: High degree (not supported)
    '8 * X^3 - 6 * X^1 + 0 * X^2 = 3 * X^0'  # Expected: Degree too high
)

# Error test cases (invalid input)
error_test_cases=(
    # Invalid format: missing "X" in term
    '5 * 0 + 4 * X^1 = 4 * X^0'  # Expected: Error due to invalid term format

    # Invalid format: exponent not provided
    '5 * X + 4 * X^1 = 4 * X^0'  # Expected: Error because 'X' should be 'X^1'

    # Missing equality sign
    '5 * X^0 + 4 * X^1 - 9.3 * X^2'  # Expected: Error due to missing '='

    # Invalid character in the equation
    '5 * X^0 + 4 * X^1 - abc * X^2 = 1 * X^0'  # Expected: Error due to 'abc'

    # Completely invalid format
    'this is not a polynomial'  # Expected: Error due to unrecognized format

    # Empty input
    ''  # Expected: Error due to empty input
)

# Loop through valid test cases
echo "=== Testing Valid Cases ==="
for test_case in "${valid_test_cases[@]}"
do
    echo "Testing case: $test_case"
    python3 "$PYTHON_SCRIPT" "$test_case"
    echo ""
done

# Loop through error test cases
echo "=== Testing Error Cases ==="
for test_case in "${error_test_cases[@]}"
do
    echo "Testing case: $test_case"
    python3 "$PYTHON_SCRIPT" "$test_case"
    echo ""
done
