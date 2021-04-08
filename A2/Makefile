all: omp-exp mpi-exp
omp-exp: omp-100 omp-400 omp-1000 omp-4000 omp-10000
mpi-exp1: mpi-100 mpi-400 mpi-1000 mpi-4000 mpi-10000
mpi-exp2: mpi-1 mpi-2 mpi-4 mpi-6 mpi-8

test:
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=6 -D TEST=1 -o omp_out && ./omp_out
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=6 -D TEST=1 -o mpi_out && mpirun --use-hwthread-cpus -v -np 8 mpi_out

omp-100:
	@echo "Running for N = 100";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=100 -o omp_out && ./omp_out

omp-400:
	@echo "Running for N = 400";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=400 -o omp_out && ./omp_out

omp-1000:
	@echo "Running for N = 1000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=1000 -o omp_out && ./omp_out

omp-4000:
	@echo "Running for N = 4000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=4000 -o omp_out && ./omp_out

omp-10000:
	@echo "Running for N = 10000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=10000 -o omp_out && ./omp_out


mpi-100:
	@echo "Running for N = 100";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=100 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-400:
	@echo "Running for N = 400";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=400 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-1000:
	@echo "Running for N = 1000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=1000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-4000:
	@echo "Running for N = 4000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=4000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-10000:
	@echo "Running for N = 10000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=10000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-1:
	@echo "Running for 1 Process";
	@mpic++ matrix_ops_mpi.cpp -O3 -o mpi_out && mpirun --use-hwthread-cpus -np 1 mpi_out

mpi-2:
	@echo "Running for 2 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -o mpi_out && mpirun --use-hwthread-cpus -np 2 mpi_out

mpi-4:
	@echo "Running for 4 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -o mpi_out && mpirun --use-hwthread-cpus -np 4 mpi_out

mpi-6:
	@echo "Running for 6 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -o mpi_out && mpirun --use-hwthread-cpus -np 6 mpi_out

mpi-8:
	@echo "Running for 8 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out
