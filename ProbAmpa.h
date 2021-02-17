#pragma once

#include "Mechanism.h"
#include "TimemUtils.h"

class ProbAmpa : public Mechanism {
    /* note: if you don't use -qalias compiler option,
     * you should use __restrict__*/
    double* __restrict__ p_0;
    double* __restrict__ p_1;
    double* __restrict__ p_2;
    double* __restrict__ p_3;
    double* __restrict__ p_4;
    double* __restrict__ p_5;
    double* __restrict__ p_6;
    double* __restrict__ p_7;
    double* __restrict__ p_8;
    double* __restrict__ p_9;
    double* __restrict__ p_10;
    double* __restrict__ p_11;
    double* __restrict__ p_12;
    double* __restrict__ p_13;
    double* __restrict__ p_14;
    double* __restrict__ p_15;
    double* __restrict__ p_16;
    double* __restrict__ p_17;
    double* __restrict__ p_18;
    double* __restrict__ p_19;
    double* __restrict__ p_20;
    double* __restrict__ p_21;
    double* __restrict__ p_22;
    double* __restrict__ p_23;
    double* __restrict__ p_24;
    double* __restrict__ p_25;
    double* __restrict__ p_26;
    double* __restrict__ p_27;
    double* __restrict__ p_28;
    double* __restrict__ p_29;
    double* __restrict__ p_30;
    double* __restrict__ p_31;
    double* __restrict__ p_32;
    double* __restrict__ p_33;
    double* __restrict__ p_34;
    double* __restrict__ p_35;
    double* __restrict__ p_36;
    double* __restrict__ p_37;
    double* __restrict__ p_38;


    void init_mechanism();
    double current_aos(double* p, double v);
    double current_soa(int i, double v);
    double current_xsoa(double* p, double v, int i, int _cntml);

    TimemUtils* t;

  public:
    ProbAmpa(int n, bool aos = false, bool soa = true)
        : Mechanism(n, aos, soa, 39) {
        t = new TimemUtils();
        init_mechanism();
    }

    void state_aos();
    void state_soa();
    void state_xsoa();

    void cur_aos();
    void cur_soa();
    void cur_xsoa();

    double* get_soa_data() {
        return pdata_soa;
    }

    double* get_aos_data() {
        return pdata_aos;
    }

    void compute() {
	    #pragma omp barrier
#if 0
        t->start();
        cur_aos();
	    #pragma omp barrier
        #pragma omp single
        t->stop("ProbAmpa Cur AoS");
#endif

	    #pragma omp barrier
        t->start();
        for(int i=0; i<50; i++) {
            cur_soa();
        }
	    #pragma omp barrier
        #pragma omp single
        t->stop("ProbAmpa Cur SoA");
    }

    ~ProbAmpa() {
        // nothing to do here
    }
};
