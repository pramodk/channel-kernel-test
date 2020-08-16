CXX=g++

CFLAGS += "-O2"
LDFLAGS += ""

DEPS = Na.h ProbAmpa.h TimeUtils.h Mechanism.h
OBJ =  Mechanism.o Na.o ProbAmpa.o main.o

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CXX) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(EXTRA_FLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core *.lst main
