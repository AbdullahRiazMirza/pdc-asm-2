#include <iostream>
#include <omp.h>

int main() {
    int dim = 100;
    double a[dim][dim], b[dim][dim], c[dim][dim];

    // Initialize matrices a and b
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            a[i][j] = 1.0;
            b[i][j] = 1.0;
            c[i][j] = 0.0; 
        }
    }

    // Define chunk sizes in an array
    int chunk_sizes[] = {1, 20, 100};

    // Test for different chunk sizes
    for (int cs = 0; cs < 3; cs++) {
        int chunk_size = chunk_sizes[cs];
        double start_time = omp_get_wtime();

        // Parallel region with guided scheduling
        #pragma omp parallel shared(a, b, c, dim) num_threads(4)
        {
            #pragma omp for schedule(guided, chunk_size)
            for (int i = 0; i < dim; i++) {
                for (int j = 0; j < dim; j++) {
                    for (int k = 0; k < dim; k++) {
                        c[i][j] += a[i][k] * b[k][j];
                    }
                }
            }
        }

        double end_time = omp_get_wtime();
        std::cout << "Guided scheduling, Chunk Size: " << chunk_size << ", Elapsed Time: " << end_time - start_time << " seconds." << std::endl;
    }

    return 0;
}
