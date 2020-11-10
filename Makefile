CXX=g++
CFLAGS=-O2

ifdef CRAY
CXX=CC
CFLAGS += -O2  -h msgs
CFLAGS = -h report=v -homp
endif

DEPS = Na.h ProbAmpa.h TimeUtils.h Mechanism.h
OBJ =  Mechanism.o Na.o ProbAmpa.o main.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core *.lst main
