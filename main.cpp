#include <iostream>
#include <string.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "Na.h"
#include "ProbAmpa.h"
#include "TimemUtils.h"

int main(int argc, char* argv[]) {
    int num_instances = 5000000;
    TimemUtils t;

    if (argc < 2) {
        std::cout << "Pass number of mechanisms as an argument,";
        std::cout << "using default " << num_instances << " instances" << std::endl;
    } else {
        num_instances = atoi(argv[1]);
    }

    int num_threads = 1;

    #ifdef _OPENMP
        #pragma omp parallel
        {
            #pragma omp master
            {
                num_threads = omp_get_num_threads();
            }
        }
    #endif

    std::cout << "\n Channel Instances : " <<  num_instances << " using threads " << num_threads << std::endl;

    #pragma omp parallel
    {
        Na channel_a(num_instances/num_threads);
        ProbAmpa channel_b(num_instances/num_threads);

        #pragma omp barrier

        #pragma omp single
        {
            std::cout << "===== INITIALIZATION DONE ====\n";
            std::cout << "Total memory usage: " << t.mem_report() << " MB" << std::endl;
        }

        channel_a.compute();
        channel_b.compute();
    }

    std::cout << std::endl;
}
