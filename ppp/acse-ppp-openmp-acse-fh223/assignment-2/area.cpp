#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>

#define NPOINTS 5000
#define MAXITER 1000

struct complex {
    double real;
    double imag;
};

int main() {
    int numoutside = 0;

    // Use OpenMP accurate timer.
    double start = omp_get_wtime();

    // Calculate area of Mandelbrot set.
    // Use dynamic scheduling with chunk size 10 to balance load.
    // Use reduction instead of atomic to reduce time taken.
    #pragma omp parallel for reduction(+:numoutside) schedule(dynamic, 10)
    for (int i = 0; i < NPOINTS; i++) {
        for (int j = 0; j < NPOINTS; j++) {
            struct complex c, z;
            c.real = -2.0 + 3 * (double)(i) / (double)(NPOINTS);
            c.imag = -1.5 + 3 * (double)(j) / (double)(NPOINTS);

            z = c;
            for (int iter = 0; iter < MAXITER; iter++) {
                double ztemp = (z.real * z.real) - (z.imag * z.imag) + c.real;
                z.imag = z.real * z.imag * 2 + c.imag;
                z.real = ztemp;
                if ((z.real * z.real + z.imag * z.imag) > 4.0) {
                    numoutside++;
                    break;
                }
            }
        }
    }

    // Use OpenMP accurate timer.
    double finish = omp_get_wtime();

    // Calculate area and error.
    double area = 3 * 3 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);
    double error = area / (double)NPOINTS;

    // Output results.
    std::cout << "Area of Mandelbrot set = " << area << " +/- " << error << std::endl;
    // Output time taken.
    //std::cout << "Time = " << finish - start << " seconds" << std::endl;

    return 0;
}
