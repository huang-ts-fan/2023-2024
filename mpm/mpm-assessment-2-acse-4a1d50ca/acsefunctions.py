import math
import cmath


def factorial(n):
    """Compute factorial of n.
    
    >>> factorial(5)
    120
    >>> factorial(0)
    1

    """
    if n == 0:
        return 1
    return n * factorial(n-1)


def exp(x, N=100):
    """Compute e^x using Taylor series expansion.
    
    >>> exp(1)
    2.7182818284590455
    >>> exp(0)
    1.0

    """
    x = x if hasattr(x, "__iter__") else [x]
    result = [sum([val**n / factorial(n) for n in range(N)]) for val in x]
    return result if len(result) > 1 else result[0]


def sin(x, N=10):
    """Compute sin(x) using Taylor series expansion.
       
    >>> sin(0)
    0.0
    >>> sin(math.pi / 2)
    1.0

    """
    # Ensure x is a list
    x = x if hasattr(x, "__iter__") else [x]

    # Reduce each value in x to the range [-pi, pi]
    x_reduced = [(val % (2 * math.pi)) - (2 * math.pi) if val % (2 * math.pi) > math.pi else val % (2 * math.pi) for val in x]
    
    # Calculate the Taylor series expansion for each reduced value
    result = [sum([(-1)**n * val**(2*n+1) / factorial(2*n+1) for n in range(N)]) for val in x_reduced]
    
    return result if len(result) > 1 else result[0]

def cos(x, N=10):
    """Compute cos(x) using Taylor series expansion.
    
    >>> cos(0)
    1.0

    """
    # Ensure x is a list
    x = x if hasattr(x, "__iter__") else [x]
    
    # Reduce each value in x to the range [-pi, pi]
    x_reduced = [(val % (2 * math.pi)) - (2 * math.pi) if val % (2 * math.pi) > math.pi else val % (2 * math.pi) for val in x]
    
    # Calculate the Taylor series expansion for each reduced value
    result = [sum([(-1)**n * val**(2*n) / factorial(2*n) for n in range(N)]) for val in x_reduced]
    
    return result if len(result) > 1 else result[0]

def tan(x, N=10):
    """Compute tan(x) using Taylor series for sin and cos without calling them directly.
    
    
    >>> tan(0)
    0.0
    >>> tan(math.pi / 4)
    1.0

    """
    
    x = x if hasattr(x, "__iter__") else [x]
    results = []

    for val in x:
        # Reduce the value in x to the range [-pi, pi]
        val_reduced = (val % (2 * math.pi)) - (2 * math.pi) if val % (2 * math.pi) > math.pi else val % (2 * math.pi)

        # Check if reduced value is close to points where tan is undefined
        if math.isclose(val_reduced, math.pi/2, abs_tol=1e-9) or math.isclose(val_reduced, -math.pi/2, abs_tol=1e-9):
            raise ValueError("Tan is not defined for x near (2n+1)*pi/2.")

        # Compute sin(val) using Taylor series expansion
        sin_val = sum([(-1)**n * val_reduced**(2*n+1) / factorial(2*n+1) for n in range(N)])
        
        # Compute cos(val) using Taylor series expansion
        cos_val = sum([(-1)**n * val_reduced**(2*n) / factorial(2*n) for n in range(N)])
        
        if cos_val == 0:
            raise ValueError("Tan is not defined for x where cos(x) = 0.")
        
        results.append(sin_val / cos_val)

    return results if len(results) > 1 else results[0]

def gamma_function(z):
    """Compute the gamma function using the Lanczos approximation.
    
    >>> abs(gamma_function(5) - 24) < 1e-10
    True
    >>> abs(gamma_function(-0.5) - -3.5449077018110335) < 1e-10
    True

    """
    
    # Coefficients for Lanczos approximation
    g = 7
    p = [0.99999999999980993, 676.5203681218851, -1259.1392167224028,
         771.32342877765313, -176.61502916214059, 12.507343278686905,
         -0.13857109526572012, 9.9843695780195716e-6, 1.5056327351493116e-7]
    
    # If the input is an array-like, recursively apply gamma_function to each element
    try:
        iter(z)  # Checks if z is iterable
        return [gamma_function(zi) for zi in z]
    except TypeError:  # If z is not iterable
        pass

    if z.real < 0.5:
        return cmath.pi / (cmath.sin(cmath.pi * z) * gamma_function(1 - z))
    
    z -= 1
    x = p[0]
    for i in range(1, g+2):
        x += p[i] / (z + i)
    t = z + g + 0.5
    result = cmath.sqrt(2 * cmath.pi) * (t ** (z + 0.5)) * cmath.exp(-t) * x

    # Check if the result is essentially real, and if so, return it as a real number
    if abs(result.imag) < 1e-10:
        return result.real
    return result

def bessel_function(alpha, x):
    """Compute the Bessel function of the first kind using the series representation.
    
    >>> abs(bessel_function(0, 1) - 0.7651976865579666) < 1e-10
    True
    >>> abs(bessel_function(1, 1) - 0.44005058574493355) < 1e-10
    True

    """
    # If the input is an array-like, recursively apply bessel_function to each element
    try:
        iter(x)  # Checks if x is iterable
        return [bessel_function(alpha, xi) for xi in x]
    except TypeError:  # If x is not iterable
        pass
    
    sum_term = 0
    m = 0
    epsilon = 1e-15

    while True:
        term = (-1)**m / (factorial(m) * gamma_function(m + alpha + 1)) * (x / 2)**(2 * m + alpha)
        sum_term += term

        # Convergence check
        if abs(term) < epsilon:
            break
        
        m += 1

    return sum_term

# Testing


'''
import numpy as np
from scipy.special import gamma, jv

x_values = np.array([0.5, 1, 1.5, 10, 15, 20])

print(exp(x_values, 100))
print(np.exp(x_values))

print(sin(x_values))
print(np.sin(x_values))

print(cos(x_values, 30))
print(np.cos(x_values))

print(tan(x_values))
print(np.tan(x_values))

print(gamma_function(23.5))
print(gamma(23.5))

print(bessel_function(1, 3+4j))
print(jv(1, 3+4j))

'''
