#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Na.h"

void Na::init_mechanism() {
    p_0 = (double*) (pdata_soa + 0 * num_instances);
    p_1 = (double*) (pdata_soa + 1 * num_instances);
    p_2 = (double*) (pdata_soa + 2 * num_instances);
    p_3 = (double*) (pdata_soa + 3 * num_instances);
    p_4 = (double*) (pdata_soa + 4 * num_instances);
    p_5 = (double*) (pdata_soa + 5 * num_instances);
    p_6 = (double*) (pdata_soa + 6 * num_instances);
    p_7 = (double*) (pdata_soa + 7 * num_instances);
    p_8 = (double*) (pdata_soa + 8 * num_instances);
    p_9 = (double*) (pdata_soa + 9 * num_instances);
    p_10 = (double*) (pdata_soa + 10 * num_instances);
    p_11 = (double*) (pdata_soa + 11 * num_instances);
    p_12 = (double*) (pdata_soa + 12 * num_instances);
    p_13 = (double*) (pdata_soa + 13 * num_instances);
    p_14 = (double*) (pdata_soa + 14 * num_instances);
    p_15 = (double*) (pdata_soa + 15 * num_instances);
    p_16 = (double*) (pdata_soa + 16 * num_instances);
    p_17 = (double*) (pdata_soa + 17 * num_instances);
}

/* nrn_state kernel in AOS format */
void Na::state_aos() {
    int _cntml = num_instances;
    long int i;
    double* __restrict__ pdata = pdata_aos;
    double* p;

    #pragma ivdep
    for (i = 0; i < _cntml; i++) {
        p = &pdata[i * CHANNEL_LEN];

        p[8] = (0.182 * (p[16] - -35.0)) / (1.0 - (exp(-(p[16] - -35.0) / 9.0)));
        p[9] = (0.124 * (-p[16] - 35.0)) / (1.0 - (exp(-(-p[16] - 35.0) / 9.0)));

        p[6] = p[8] / (p[8] + p[9]);
        p[7] = 1.0 / (p[8] + p[9]);

        p[3] = p[3] + (1. - exp(0.01 * ((((-1.0))) / p[7]))) *
                          (-(((p[6])) / p[7]) / ((((-1.0))) / p[7]) - p[3]);
        p[12] = (0.024 * (p[16] - -50.0)) / (1.0 - (exp(-(p[16] - -50.0) / 5.0)));

        p[13] = (0.0091 * (-p[16] - 75.0)) / (1.0 - (exp(-(-p[16] - 75.0) / 5.0)));
        p[10] = 1.0 / (1.0 + exp((p[16] - -65.0) / 6.2));
        p[11] = 1.0 / (p[12] + p[13]);

        p[4] = p[4] + (1. - exp(0.01 * ((((-1.0))) / p[11]))) *
                          (-(((p[10])) / p[11]) / ((((-1.0))) / p[11]) - p[4]);
    }
}


/* nrn_state kernel in SOA formatg */
void Na::state_soa() {
    int _cntml = num_instances;
    int i;

    #pragma ivdep
    for (i = 0; i < _cntml; i++) {
        p_8[i] = (0.182 * (p_16[i] - -35.0)) / (1.0 - (exp(-(p_16[i] - -35.0) / 9.0)));
        p_9[i] = (0.124 * (-p_16[i] - 35.0)) / (1.0 - (exp(-(-p_16[i] - 35.0) / 9.0)));

        p_6[i] = p_8[i] / (p_8[i] + p_9[i]);
        p_7[i] = 1.0 / (p_8[i] + p_9[i]);

        p_3[i] = p_3[i] + (1. - exp(0.01 * ((((-1.0))) / p_7[i]))) *
                              (-(((p_6[i])) / p_7[i]) / ((((-1.0))) / p_7[i]) - p_3[i]);
        p_12[i] = (0.024 * (p_16[i] - -50.0)) / (1.0 - (exp(-(p_16[i] - -50.0) / 5.0)));

        p_13[i] = (0.0091 * (-p_16[i] - 75.0)) / (1.0 - (exp(-(-p_16[i] - 75.0) / 5.0)));
        p_10[i] = 1.0 / (1.0 + exp((p_16[i] - -65.0) / 6.2));
        p_11[i] = 1.0 / (p_12[i] + p_13[i]);

        p_4[i] = p_4[i] + (1. - exp(0.01 * ((((-1.0))) / p_11[i]))) *
                              (-(((p_10[i])) / p_11[i]) / ((((-1.0))) / p_11[i]) - p_4[i]);
    }
}

/* Na current kernel in AOS format */
void Na::cur_aos() {
    int _cntml = num_instances;
    long int i;
    double* __restrict__ pdata = pdata_aos;
    double* p;
    double v, dina, rhs;

    #pragma ivdep
    for (i = 0; i < _cntml; i++) {
        p = &pdata[i * CHANNEL_LEN];

        int id = index_array[i];
        v = VEC_V[id];
        p[5] = ppvar0[i];

        // nrn_current
        p[16] = v + 0.001;
        p[2] = p[0] * p[3] * p[3] * p[3] * p[4];
        p[1] = p[2] * (p[16] - p[5]);
        p[17] = p[1];

        dina = p[1];

        // nrn_current
        p[16] = v;
        p[2] = p[0] * p[3] * p[3] * p[3] * p[4];
        p[1] = p[2] * (p[16] - p[5]);
        rhs = p[1];

        ppvar2[i] += (dina - p[1]) / 0.001;

        p[17] = (p[17] - VEC_RHS[id]) / 0.001;
        ppvar1[i] += p[1];

        VEC_RHS[id] -= rhs;
    }
}

void Na::cur_soa() {
    int _cntml = num_instances;
    int i;
    double rhs, v, dina;

    #pragma ivdep
    for (i = 0; i < _cntml; i++) {
        int id = index_array[i];
        v = VEC_V[id];
        p_5[i] = ppvar0[i];

        // nrn_current
        p_16[i] = v + 0.001;
        p_2[i] = p_0[i] * p_3[i] * p_3[i] * p_3[i] * p_4[i];
        p_1[i] = p_2[i] * (p_16[i] - p_5[i]);
        p_17[i] = p_1[i];

        dina = p_1[i];

        // nrn_current
        p_16[i] = v;
        p_2[i] = p_0[i] * p_3[i] * p_3[i] * p_3[i] * p_4[i];
        p_1[i] = p_2[i] * (p_16[i] - p_5[i]);
        rhs = p_1[i];

        ppvar2[i] += (dina - p_1[i]) / 0.001;

        p_17[i] = (p_17[i] - VEC_RHS[id]) / 0.001;
        ppvar1[i] += p_1[i];

        VEC_RHS[id] -= rhs;
    }
}
