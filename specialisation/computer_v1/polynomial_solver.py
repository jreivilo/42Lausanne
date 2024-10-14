import re
import math
import sys
from fractions import Fraction

def parse_term(term):
    """Parses a single term like '5 * X^2' or 'X' and returns (coefficient, exponent)"""
    term = term.strip().replace(' ', '')  # Remove any spaces

    # Check if the term is a valid polynomial term (handle cases like '5 * 0')
    if re.match(r'([-+]?\d*\.?\d*)\*0$', term):
        return 0.0, 0  # Any term multiplied by 0 is just 0

    # Handle cases where the exponent is omitted (e.g., '5 * X' should be '5 * X^1')
    if re.match(r'([-+]?\d*\.?\d*)\*?X$', term):
        # Implied exponent 1 (e.g., '5 * X' -> '5 * X^1')
        coefficient = re.match(r'([-+]?\d*\.?\d*)\*?X$', term).group(1)
        coefficient = float(coefficient) if coefficient else 1.0
        return coefficient, 1
    
    # General case with explicit exponent
    match = re.match(r'([-+]?\d*\.?\d*)\*?X\^(\d+)', term)
    if match:
        coefficient = float(match.group(1)) if match.group(1) else 1.0
        exponent = int(match.group(2))
        return coefficient, exponent
    
    # If it's just a constant term (e.g., '5')
    match = re.match(r'([-+]?\d*\.?\d*)$', term)
    if match:
        coefficient = float(match.group(1)) if match.group(1) else 0.0
        return coefficient, 0

    # Raise an error if the term format is invalid
    raise ValueError(f"Invalid term format: {term}")

def parse_polynomial(equation):
    """Parses an equation into left and right side polynomials"""
    left, right = equation.split('=')
    left_terms = re.split(r'(?=[+-])', left)
    right_terms = re.split(r'(?=[+-])', right)

    def add_terms(terms, sign=1):
        """Converts terms to a dictionary of exponents -> coefficients"""
        poly_dict = {}
        for term in terms:
            if 'X' in term or '*' in term:  # Handle terms with variables or constants
                coeff, exp = parse_term(term)
            else:
                coeff, exp = float(term), 0  # It's just a constant
            poly_dict[exp] = poly_dict.get(exp, 0) + sign * coeff
        return poly_dict

    left_poly = add_terms(left_terms, sign=1)
    right_poly = add_terms(right_terms, sign=-1)

    return left_poly, right_poly

def reduce_polynomial(left_poly, right_poly):
    """Simplifies the polynomial by combining like terms"""
    reduced_poly = {}
    for exp in set(left_poly.keys()).union(right_poly.keys()):
        coeff = left_poly.get(exp, 0) + right_poly.get(exp, 0)
        if coeff != 0:
            reduced_poly[exp] = coeff
    return reduced_poly

def format_fraction(value):
    """Formats a float as an irreducible fraction"""
    fraction = Fraction(value).limit_denominator()
    return f"{fraction.numerator}/{fraction.denominator}" if fraction.denominator != 1 else f"{fraction.numerator}"

def solve_polynomial(poly):
    """Solves the polynomial equation based on its degree and prints intermediary steps"""
    degree = max(poly.keys(), default=0)
    print(f"Polynomial degree: {degree}")
    
    if degree == 2:
        # Solve quadratic ax^2 + bx + c = 0
        a = poly.get(2, 0)
        b = poly.get(1, 0)
        c = poly.get(0, 0)
        print(f"Quadratic equation: {a} * X^2 + {b} * X + {c} = 0")
        
        discriminant = b**2 - 4*a*c
        print(f"Discriminant (Δ) = b^2 - 4ac = {b}^2 - 4 * {a} * {c} = {discriminant}")
        
        if discriminant > 0:
            root1 = (-b + math.sqrt(discriminant)) / (2 * a)
            root2 = (-b - math.sqrt(discriminant)) / (2 * a)
            print(f"Solving roots using (-b ± √Δ) / 2a:")
            print(f"Root 1 = (-{b} + √{discriminant}) / (2 * {a}) = {root1}")
            print(f"Root 2 = (-{b} - √{discriminant}) / (2 * {a}) = {root2}")
            return f"Two real solutions: {root1}, {root2}"
        elif discriminant == 0:
            root = -b / (2 * a)
            print(f"Solving root using -b / 2a = -{b} / (2 * {a}) = {root}")
            return f"One real solution (as fraction): {format_fraction(root)}"
        else:
            real_part = -b / (2 * a)
            imaginary_part = math.sqrt(-discriminant) / (2 * a)
            print(f"Discriminant is negative, roots are complex:")
            print(f"Real part = -{b} / (2 * {a}) = {real_part}")
            print(f"Imaginary part = √{-discriminant} / (2 * {a}) = {imaginary_part}")
            return f"Two complex solutions: {real_part} ± {imaginary_part}i"
    elif degree == 1:
        # Solve linear bx + c = 0
        b = poly.get(1, 0)
        c = poly.get(0, 0)
        print(f"Linear equation: {b} * X + {c} = 0")
        if b != 0:
            solution = -c / b
            print(f"Solving for X: X = -{c} / {b} = {solution}")
            return f"One real solution (as fraction): {format_fraction(solution)}"
        else:
            return "No solution" if c != 0 else "Infinite solutions"
    elif degree == 0:
        # Handle constant case c = 0
        return "Infinite solutions" if poly.get(0, 0) == 0 else "No solution"
    else:
        return "The polynomial degree is too high to solve."

def main():
    # Check if the equation is passed as a command-line argument
    if len(sys.argv) != 2:
        print("Usage: python3 polynomial_solver.py 'equation'")
        sys.exit(1)

    equation = sys.argv[1]  # Take the equation from the command-line argument
    try:
        left_poly, right_poly = parse_polynomial(equation)
        reduced_poly = reduce_polynomial(left_poly, right_poly)
        
        # Display reduced form
        reduced_form = " + ".join([f"{coeff} * X^{exp}" for exp, coeff in sorted(reduced_poly.items(), reverse=True)])
        print(f"Reduced form: {reduced_form} = 0")
        
        # Solve the polynomial with intermediary steps
        solution = solve_polynomial(reduced_poly)
        print(solution)
    except Exception as e:
        print(f"Error: {e}")

# Entry point of the script
if __name__ == "__main__":
    main()
