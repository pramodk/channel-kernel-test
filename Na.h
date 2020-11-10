
#include "Mechanism.h"
#include "TimeUtils.h"

class Na : public Mechanism {
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

    void init_mechanism();

    TimeUtils* t;

  public:
    Na(int n, bool aos = true, bool soa = true)
        : Mechanism(n, aos, soa, 18) {
        t = new TimeUtils();
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
#if 0
	#pragma omp barrier
        t->start();
        state_aos();
	#pragma omp barrier
	#pragma omp single
        t->stop("Na State AoS");
#endif

        t->start();
        state_soa();
	#pragma omp barrier
	#pragma omp single
        t->stop("Na State SoA");

#if 0
        t->start();
        cur_aos();
	#pragma omp barrier
	#pragma omp single
        t->stop("Na Current AoS");
#endif

        t->start();
        cur_soa();
	#pragma omp barrier
	#pragma omp single
        t->stop("Na Current SoA");
    }

    ~Na() {
        // nothing to do here
    }
};
