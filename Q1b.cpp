#include <iostream>
#include <cmath>
#include <omp.h>

#define NUM_THREADS 4  // Number of threads to use in parallel

// Function to integrate
double f(double y) {
    return 1.0 / (1 + y + y * y + pow(y, 4));
}

// Trapezoidal rule implementation with parallelization using OpenMP
double trapezoidalRule(double a, double b, int n) {
    double h = (b - a) / n;  // Step size
    double sum = 0.0;

    // Use OpenMP to parallelize the loop with reduction for summing
    #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:sum)
    for (int i = 1; i < n; i++) {
        double y = a + i * h;
        sum += f(y);
    }

    // Add the contribution from the first and last points
    sum += 0.5 * (f(a) + f(b));

    return sum * h;
}

int main() {
    double a = 5.0, b = 10.0;
    int n = 1000000; // Number of intervals

    // Start measuring time
    double start_time = omp_get_wtime();

    // Calculate the integral using the trapezoidal rule
    double result = trapezoidalRule(a, b, n);

    // End measuring time
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // Output the result and the time taken
    std::cout << "Integral from " << a << " to " << b << " is approximately: " << result << std::endl;
    std::cout << "Elapsed time: " << elapsed_time << " seconds" << std::endl;

    return 0;
}


//SERIAL TIME=1.23s
//PARALLEL TIME (4 Threads)=0.343s