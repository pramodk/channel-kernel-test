#pragma once

class Mechanism {
  protected:
    /* New Vectors */
    double* __restrict__ VEC_RHS;
    double* __restrict__ VEC_V;

    double* ppvar;
    double* __restrict__ ppvar0;
    double* __restrict__ ppvar1;
    double* __restrict__ ppvar2;

    const int CHANNEL_LEN;
    const int ION_LEN;
    const int MAX_RANDOM;

    /*AoS format*/
    double* pdata_aos;

    /*SoA format*/
    double* pdata_soa;

    int* index_array;

    bool enable_aos;
    bool enable_soa;

    void init_mechanism();

  public:
    int num_instances;

    Mechanism(int n, bool aos, bool soa, int cha_len)
        : CHANNEL_LEN(cha_len)
        , ION_LEN(3)
        , MAX_RANDOM(20) {
        num_instances = n;
        enable_aos = aos;
        enable_soa = soa;
        init_mechanism();
    }

    double* get_soa_data() {
        return pdata_soa;
    }

    double* get_aos_data() {
        return pdata_aos;
    }

    ~Mechanism() {
        if (enable_aos)
            delete[] pdata_aos;
        if (enable_soa)
            delete[] pdata_soa;
        delete[] ppvar;
        delete[] VEC_V;
        delete[] VEC_RHS;
        delete[] index_array;
    }
};
