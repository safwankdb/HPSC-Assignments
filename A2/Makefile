all: omp mpi

omp:
	g++ -O3 -fopenmp matrix_ops_omp.cpp -o omp_out && ./omp_out

mpi:
	mpic++ matrix_ops_mpi.cpp -O3 && mpirun --use-hwthread-cpus -np 8 a.out
