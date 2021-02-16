CXX=g++
CFLAGS=-O3 -fopt-info -fopt-info-optimized -fopt-info-missed -mcpu=native -lm -fopenmp

ifdef ARMGCC
ARMPL_DIR=/lustre/software/aarch64/tools/arm-compiler/20.3/armpl-20.3.0_A64FX_RHEL-8_gcc_aarch64-linux
CFLAGS=-O3 -fopt-info -fopt-info-optimized -fopt-info-missed -mcpu=native -L$ARMPL_DIR/lib -lamath -lm -fopenmp
endif

ifdef CRAY
CXX=CC
CFLAGS = -O3 -h report=v -homp -h list=a
endif

ifdef ARM
CXX=armclang++
CFLAGS=-O3 -Ofast -g -mcpu=native -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize -Rpass-missed=loop-vectorize -fsimdmath
endif

ifdef INTEL
CXX=icc
CFLAGS = -O2  -qopt-report=5 -qopenmp -xHost
endif

DEPS = Na.h ProbAmpa.h TimemUtils.h Mechanism.h
OBJ =  Mechanism.o Na.o ProbAmpa.o main.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core *.lst main
