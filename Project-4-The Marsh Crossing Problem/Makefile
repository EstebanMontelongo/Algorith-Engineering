
CXX = g++ -std=c++17 -Wall

all: run_test crossing_timing

run_test: crossing_test
	./crossing_test

headers: rubrictest.hpp crossing_types.hpp crossing_algs.hpp

gnomes_test: headers crossing_test.cpp
	${CXX} crossing_test.cpp -o crossing_test

gnomes_timing: headers crossing_timing.cpp
	${CXX} crossing_timing.cpp -o crossing_timing

clean:
	rm -f crossing_test crossing_timing
