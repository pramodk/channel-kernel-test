#pragma once

#include <fstream>
#include <malloc.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

class TimemUtils {
    struct timeval tvBegin;
    struct timeval tvEnd;

  public:
    void start() {
        gettimeofday(&tvBegin, NULL);
    }

    void stop(const char* msg, int tid = 0) {
        struct timeval tvDiff;
        gettimeofday(&tvEnd, NULL);

        long int diff = (tvEnd.tv_usec + 1000000 * tvEnd.tv_sec) -
                        (tvBegin.tv_usec + 1000000 * tvBegin.tv_sec);

        tvDiff.tv_sec = diff / 1000000;
        tvDiff.tv_usec = diff % 1000000;

        printf("\n Thread: %d   %20s     Elapsed Time :: %ld.%06d",
               tid,
               msg,
               tvDiff.tv_sec,
               tvDiff.tv_usec);

        // should we re-initialzie?
        tvBegin = (struct timeval){0};
    }

    double mem_report() {
        double usageMB = 0;
        std::ifstream file("/proc/self/statm");
        if (file.is_open()) {
            unsigned long long int data_size;
            file >> data_size >> data_size;
            file.close();
            usageMB = (data_size * sysconf(_SC_PAGESIZE)) / (1024.0 * 1024.0);
        } else {
            struct mallinfo m = mallinfo();
            usageMB = (m.hblkhd + m.uordblks) / (1024.0 * 1024.0);
        }
        return usageMB;
    }
};
