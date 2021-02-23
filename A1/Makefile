# Usage
## make: compile all and test timings
## make clean: remove binaries

.PHONY: compile test clean all

all: compile test

compile:
	@echo "Compiling Trapezoid Serial";
	@g++ trapezoid_serial.cpp -O3 -o trapezoid_serial
	@echo "Compiling Trapezoid Parallel";
	@g++ trapezoid_parallel.cpp -O3 -fopenmp -o trapezoid_parallel
	@echo "Compiling Monte Carlo Serial";
	@g++ montecarlo_serial.cpp -O3 -o montecarlo_serial
	@echo "Compiling Monte Carlo Parallel";
	@g++ montecarlo_parallel.cpp -O3 -fopenmp -o montecarlo_parallel
	@echo


test:
	@echo "Testing Trapezoid Serial";
	@./trapezoid_serial
	@echo "\nTesting Trapezoid Parallel";
	@./trapezoid_parallel
	@echo "\nTesting Monte Carlo Serial";
	@./montecarlo_serial
	@echo "\nTesting Monte Carlo Parallel";
	@./montecarlo_parallel
	@echo

clean:
	@echo "Removing Trapezoid Serial";
	@rm trapezoid_serial
	@echo "Removing Trapezoid Parallel";
	@rm trapezoid_parallel
	@echo "Removing Monte Carlo Serial";
	@rm montecarlo_serial
	@echo "Removing Monte Carlo Parallel";
	@rm montecarlo_parallel
	@echo
