[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/DuPH9OCA)

# MPM assessment 2

## <font color = red > Note: Make sure you have imported the base function before using the complex function.  
For example: 

We use some constant terms from the math library (e.g., π and e) and also some complex (real and imaginary) arithmetic functions from the cmath library.

To ensure that the functions are used correctly, remember to install them.

Most of the functions we have implemented are based on Taylor Expansion, so the factorial function needs to be imported before we can use these functions.  
  
Bessel's function is based on our custom gamma function, so make sure the current file has access to our gamma function before using it.</font>

After importing the predecessor functions correctly, you can use our defined functions to do some arithmetic on trigonometric and Bessel's functions.

## How to use

Once you have installed our custom library, you can use it in any python file: 

The easiest way to do this is to import the whole library directly.
`import acsefunctions`
and then you can use the functions we've defined directly.

If you only want to import some specific functions from that library, that's certainly possible:
`from acsefunctions import sin, cos`
But remember, like mentioned before, you need to import the relevant predecessor functions to make sure our custom function runs smoothly.

Our custom function is stored in the file acsefunctions.py (in the comments at the end of the file there is code for testing it with Numpy, you can enable it at any time), and there is also a corresponding test file test_acsefunctions.py (which compares the output with the output of the built-in libraries to determine if our custom function are correct or not).