#include <iostream>
#include <fstream>
#include <vector>

# define NPOINTS 5000
# define MAXITER 1000

struct complex{
  double real;
  double imag;
};

int main(){
  int numoutside = 0;

  // Outer loops run over npoints, initialise z=c
  // Inner loop has the iteration z=z*z+c, and threshold test

  // double start = ...; // Use OpenMP accurate timer.
  
  for (int i=0; i<NPOINTS; i++) {
    for (int j=0; j<NPOINTS; j++) {
      struct complex c;
      c.real = -2.0+3*(double)(i)/(double)(NPOINTS);
      c.imag = -1.5+3*(double)(j)/(double)(NPOINTS);

      struct complex z=c;
      int iter = 0;
      for (iter=0; iter<MAXITER; iter++) {
	      double ztemp=(z.real*z.real)-(z.imag*z.imag)+c.real;
	      z.imag=z.real*z.imag*2+c.imag; 
	      z.real=ztemp; 
	      if ((z.real*z.real+z.imag*z.imag)>4.0e0) {
	        numoutside++; 
	        break;
	      }
      }
    }
  }

  // double finish = ...; // Use OpenMP accurate timer.  

  // Calculate area and error and output the results

  double area=3*3*(double)(NPOINTS*NPOINTS-numoutside)/(double)(NPOINTS*NPOINTS);
  double error=area/(double)NPOINTS;

  std::cout<<"Area of Mandlebrot set = "<<area<<" +/- "<<error<<std::endl;
  // std::cout<<"Time = "<<finish-start<<" seconds"<<std::endl;

  return 0;
}
