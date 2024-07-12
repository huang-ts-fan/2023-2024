#include <iostream>
#include <gperftools/profiler.h>
#include <cmath>

// compilation on mac:
// g++ -std=c++20 -o estimate_pi estimate_pi.cpp -L /opt/homebrew/lib -I /opt/homebrew/include -lprofiler -g

// Function to store an array of double values created by rand()
void storeRand(double* arr, int N) {
    for (int i = 0; i < N; ++i) {
        arr[i] = (double)rand() / RAND_MAX;
    }
}

double sqrtPOW(double x) {
    // return the square root of x
    return std::pow(x, 0.5);
}

double sqrtNR(double x, double tolerance=0.000001) {
    if (x < 0) {
        // Handle negative input (optional)
        // You can throw an exception or return an error message.
        // For now, let's return -1.0 as an indicator of invalid input.
        return -1.0;
    } else if (x == 0) {
        return 0.0;
    } else {
        double guess = 1.;

        while (std::abs(guess * guess - x) > tolerance) {
            guess = (guess + x / guess) / 2;
        }
        return guess;
    }
}

double distance(double x, double y, double tolerance) {
    // overload the tolerance value 
    if (tolerance < 0) {
        return sqrtPOW(x * x + y * y);
    } else {
        return sqrtNR(x * x + y * y, tolerance);
    }
}

// Function to estimate the value of pi using the Monte Carlo method
double estimatePi(int N, double tolerance) {
    int num_points_inside_circle = 0;

    double* x_arr = new double[N];
    double* y_arr = new double[N];
    
    storeRand(x_arr, N);
    storeRand(y_arr, N);

    for (int i = 0; i < N; ++i) {
        double x = x_arr[i];
        double y = y_arr[i];
        if (distance(x, y, tolerance) <= 1) {
            num_points_inside_circle++;
        }
    }

    delete[] x_arr;
    delete[] y_arr;

    return 4.0 * num_points_inside_circle / N;
}

// Function to estimate the value of pi using the Monte Carlo method
// this time without creating a whole array of x and y, instead
// we create them on the fly
double estimatePiOnTheFly(int N, double tolerance) {
    int num_points_inside_circle = 0;

    for (int i = 0; i < N; ++i) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (distance(x, y, tolerance) <= 1) {
            num_points_inside_circle++;
        }
    }

    return 4.0 * num_points_inside_circle / N;
}

int main() {

    int N = 1000000; // Change N to any positive integer value

    ProfilerStart("pi1.prof"); // Start profiling section and save to file
    for (int i = 0; i < 1000; i++) {
        double result = estimatePi(N, -1);
        if (i % 100 == 0)
            std::cout << "1. Estimate of pi using " << N << " points: " << result << " : " << i << std::endl;
    }
    ProfilerStop(); // Stop profiling section
    std::cout << "\n";

    ProfilerStart("pi2.prof"); // Start profiling section and save to file
    for (int i = 0; i < 1000; i++) {
        double result = estimatePi(N, 0.00001);
        if (i % 100 == 0)
            std::cout << "2. Estimate of pi using " << N << " points: " << result << " : " << i << std::endl;
    }
    ProfilerStop(); // Stop profiling section
    std::cout << "\n";

    ProfilerStart("pi3.prof"); // Start profiling section and save to file
    for (int i = 0; i < 1000; i++) {
        double result = estimatePi(N, 0.0000001);
        if (i % 100 == 0)
            std::cout << "3. Estimate of pi using " << N << " points: " << result << " : " << i << std::endl;
    }
    ProfilerStop(); // Stop profiling section
    std::cout << "\n";

    ProfilerStart("pi4.prof"); // Start profiling section and save to file
    for (int i = 0; i < 1000; i++) {
        double result = estimatePiOnTheFly(N, -1);
        if (i % 100 == 0)
            std::cout << "4. Estimate of pi using " << N << " points: " << result << " : " << i << std::endl;
    }
    ProfilerStop(); // Stop profiling section
    std::cout << "\n";

    ProfilerStart("pi5.prof"); // Start profiling section and save to file
    for (int i = 0; i < 1000; i++) {
        double result = estimatePiOnTheFly(N, 0.00001);
        if (i % 100 == 0)
            std::cout << "5. Estimate of pi using " << N << " points: " << result << " : " << i << std::endl;
    }
    ProfilerStop(); // Stop profiling section
    std::cout << "\n";

    ProfilerStart("pi6.prof"); // Start profiling section and save to file
    for (int i = 0; i < 1000; i++) {
        double result = estimatePiOnTheFly(N, 0.0000001);
        if (i % 100 == 0)
            std::cout << "6. Estimate of pi using " << N << " points: " << result << " : " << i << std::endl;
    }
    ProfilerStop(); // Stop profiling section
    std::cout << "\n";

    return 0;
}