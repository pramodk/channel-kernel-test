#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Mechanism.h"

void Mechanism::init_mechanism() {
    int i, j;
    long int seed = 0;
    double r;

    if (enable_aos) {
        pdata_aos = (double*) malloc(sizeof(double) * num_instances * CHANNEL_LEN);
    }

    if (enable_soa) {
        pdata_soa = (double*) malloc(sizeof(double) * num_instances * CHANNEL_LEN);
    }

    VEC_RHS = (double*) malloc(sizeof(double) * num_instances);
    VEC_V = (double*) malloc(sizeof(double) * num_instances);

    index_array = (int*) malloc(sizeof(int) * num_instances);
    ppvar = (double*) malloc(sizeof(double) * num_instances * ION_LEN);

    ppvar0 = (double*) (ppvar + 0 * num_instances);
    ppvar1 = (double*) (ppvar + 1 * num_instances);
    ppvar2 = (double*) (ppvar + 2 * num_instances);

    seed = time(NULL);
    srand(seed);

    double inc = 0.001;

    for (i = 0; i < num_instances; i++) {
        for (j = 0; j < CHANNEL_LEN; j++) {
            r = inc;
            inc += 0.000001;
            //r = (rand() % MAX_RANDOM) + 10.1;

            // will be random
            if (enable_aos)
                pdata_aos[i * CHANNEL_LEN + j] = r;
            if (enable_soa)
                pdata_soa[j * num_instances + i] = r;
        }

        VEC_RHS[i] = r;
        VEC_V[i] = r;

        // will be random
        index_array[i] = i;

        ppvar0[i] = r;
        ppvar1[i] = r;
        ppvar2[i] = r;
    }
}
