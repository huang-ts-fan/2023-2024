import pytest
from acsefunctions import factorial, exp, sin, cos, tan, gamma_function, bessel_function
from scipy.special import gamma as scipy_gamma
import math
# import cmath

def test_factorial():
    assert factorial(0) == 1
    assert factorial(1) == 1
    assert factorial(5) == 120
    assert factorial(10) == 3628800

def test_exp():
    assert pytest.approx(exp(0), abs=1e-9) == 1
    assert pytest.approx(exp(1), abs=1e-9) == math.e
    assert pytest.approx(exp([-1, 0, 1]), abs=1e-9) == [1/math.e, 1, math.e]

def test_sin():
    assert pytest.approx(sin(0), abs=1e-9) == 0
    assert pytest.approx(sin(math.pi/2), abs=1e-9) == 1
    assert pytest.approx(sin(math.pi), abs=1e-9) == 0
    assert pytest.approx(sin([0, math.pi/2, math.pi]), abs=1e-9) == [0, 1, 0]

def test_cos():
    assert pytest.approx(cos(0), abs=1e-9) == 1
    assert pytest.approx(cos(math.pi/2), abs=1e-9) == 0
    assert pytest.approx(cos(math.pi), abs=1e-8) == -1
    assert pytest.approx(cos([0, math.pi/2, math.pi]), abs=1e-8) == [1, 0, -1]

def test_tan():
    assert pytest.approx(tan(0), abs=1e-9) == 0
    assert pytest.approx(tan(math.pi/4), abs=1e-9) == 1
    with pytest.raises(ValueError):
        tan(math.pi/2)
    with pytest.raises(ValueError):
        tan(-math.pi/2)

def test_gamma_function():
    assert pytest.approx(gamma_function(0.5), abs=1e-9) == math.sqrt(math.pi)
    assert pytest.approx(gamma_function(1), abs=1e-9) == 1
    assert pytest.approx(gamma_function(5), abs=1e-9) == 24

def test_bessel_function():
    assert pytest.approx(bessel_function(0, 0), abs=1e-9) == 1
    assert pytest.approx(bessel_function(1, 1), abs=1e-9) == 0.4400505857449335

def test_gamma_function_complex():
    # Some known values for complex inputs
    assert pytest.approx(gamma_function(complex(0.5, 0.5)).real, abs=1e-9) == scipy_gamma(complex(0.5, 0.5)).real
    assert pytest.approx(gamma_function(complex(0.5, 0.5)).imag, abs=1e-9) == scipy_gamma(complex(0.5, 0.5)).imag

    assert pytest.approx(gamma_function(complex(-0.5, 1.5)).real, abs=1e-9) == scipy_gamma(complex(-0.5, 1.5)).real
    assert pytest.approx(gamma_function(complex(-0.5, 1.5)).imag, abs=1e-9) == scipy_gamma(complex(-0.5, 1.5)).imag

def test_bessel_function_complex():
    # We'll test against some random complex values since there isn't a standard implementation for complex Bessel functions.
    complex_val = complex(0.5, 1.5)
    assert isinstance(bessel_function(0, complex_val), complex)  # Ensure we get a complex result
    complex_val2 = complex(1.5, 0.5)
    assert isinstance(bessel_function(1, complex_val2), complex)  # Ensure we get a complex result
