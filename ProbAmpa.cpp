#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ProbAmpa.h"
#include "TimeUtils.h"

void ProbAmpa::init_mechanism() {
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
    p_18 = (double*) (pdata_soa + 18 * num_instances);
    p_19 = (double*) (pdata_soa + 19 * num_instances);
    p_20 = (double*) (pdata_soa + 20 * num_instances);
    p_21 = (double*) (pdata_soa + 21 * num_instances);
    p_22 = (double*) (pdata_soa + 22 * num_instances);
    p_23 = (double*) (pdata_soa + 23 * num_instances);
    p_24 = (double*) (pdata_soa + 24 * num_instances);
    p_25 = (double*) (pdata_soa + 25 * num_instances);
    p_26 = (double*) (pdata_soa + 26 * num_instances);
    p_27 = (double*) (pdata_soa + 27 * num_instances);
    p_28 = (double*) (pdata_soa + 28 * num_instances);
    p_29 = (double*) (pdata_soa + 29 * num_instances);
    p_30 = (double*) (pdata_soa + 30 * num_instances);
    p_31 = (double*) (pdata_soa + 31 * num_instances);
    p_32 = (double*) (pdata_soa + 32 * num_instances);
    p_33 = (double*) (pdata_soa + 33 * num_instances);
    p_34 = (double*) (pdata_soa + 34 * num_instances);
    p_35 = (double*) (pdata_soa + 35 * num_instances);
    p_36 = (double*) (pdata_soa + 36 * num_instances);
    p_37 = (double*) (pdata_soa + 37 * num_instances);
    p_38 = (double*) (pdata_soa + 38 * num_instances);
}

inline double ProbAmpa::current_aos(double* __restrict__ p, double v) {
    double pval;
    double gmax_ProbAMPANMDA_EMS = 0.234;
    double current;

    p[36] = v;

    pval = 1.0 / (1.0 + exp(0.062 * -(p[36])) * (p[8] / 3.57));

    p[16] = gmax_ProbAMPANMDA_EMS * (p[27] - p[26]);
    p[17] = gmax_ProbAMPANMDA_EMS * (p[29] - p[28]) * pval;
    p[18] = p[16] + p[17];
    p[14] = p[16] * (p[36] - p[7]);
    p[15] = p[17] * (p[36] - p[7]);
    p[13] = p[14] + p[15];
    current = p[13];

    return current;
}

void ProbAmpa::cur_aos() {
    int _cntml = num_instances;
    long int i;
    double* __restrict__ pdata = pdata_aos;
    double* p;
    double v, rhs;

    // NOTE : typically atomic operation is needed when we
    // updated VEC_RHS. On CPU we typically we split the loop
    // if atomic operation is not supported. For now assume
    // all iterations are independent.

    #pragma ivdep
    for (i = 0; i < _cntml; i++) {
        p = &pdata[i * CHANNEL_LEN];
        int id = index_array[i];
        v = VEC_V[id];

        p[37] = current_aos(p, v + 0.001);
        rhs = current_aos(p, v);

        p[37] = (p[37] - rhs) / .001;
        p[37] *= 1.e2 / (p[12]);
        rhs *= 1.e2 / (p[12]);

        // NOTE : atomic op is needed
        VEC_RHS[id] -= rhs;
    }
}


inline double ProbAmpa::current_soa(int i, double v) {
    double pval;
    double gmax_ProbAMPANMDA_EMS = 0.234;
    double current;

    p_36[i] = v;

    pval = 1.0 / (1.0 + exp(0.062 * -(p_36[i])) * (p_8[i] / 3.57));

    p_16[i] = gmax_ProbAMPANMDA_EMS * (p_27[i] - p_26[i]);
    p_17[i] = gmax_ProbAMPANMDA_EMS * (p_29[i] - p_28[i]) * pval;
    p_18[i] = p_16[i] + p_17[i];
    p_14[i] = p_16[i] * (p_36[i] - p_7[i]);
    p_15[i] = p_17[i] * (p_36[i] - p_7[i]);
    p_13[i] = p_14[i] + p_15[i];
    current = p_13[i];

    return current;
}


void ProbAmpa::cur_soa() {
    int _cntml = num_instances;
    int i;
    double rhs, v;

    // NOTE : typically atomic operation is needed when we
    // updated VEC_RHS. On CPU we typically we split the loop
    // if atomic operation is not supported. For now assume
    // all iterations are independent.

    #pragma ivdep
    for (i = 0; i < _cntml; i++) {
        int id = index_array[i];
        v = VEC_V[id];

        p_37[i] = current_soa(i, v + 0.001);
        rhs = current_soa(i, v);

        p_37[i] = (p_37[i] - rhs) / .001;
        p_37[i] *= 1.e2 / (p_12[i]);
        rhs *= 1.e2 / (p_12[i]);

        VEC_RHS[id] -= rhs * (1.e2 / p_12[i]);
    }
}
