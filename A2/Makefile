all: omp-exp mpi-exp clean
omp-exp: omp-100 omp-400 omp-1000 omp-2000 omp-5000 omp-10000
mpi-exp: mpi-100 mpi-400 mpi-1000 mpi-2000 mpi-5000 mpi-10000
mpi-exp2: mpi-1 mpi-2 mpi-3 mpi-4 mpi-5 mpi-6 mpi-7 mpi-8

test:
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=6 -D TEST=1 -o omp_out && ./omp_out
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=6 -D TEST=1 -o mpi_out && mpirun --use-hwthread-cpus -v -np 8 mpi_out

omp-100:
	@echo "OMP Running for N = 100";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=100 -o omp_out && ./omp_out

omp-400:
	@echo "OMP Running for N = 400";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=400 -o omp_out && ./omp_out

omp-1000:
	@echo "OMP Running for N = 1000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=1000 -o omp_out && ./omp_out

omp-2000:
	@echo "OMP Running for N = 2000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2000 -o omp_out && ./omp_out

omp-5000:
	@echo "OMP Running for N = 5000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=5000 -o omp_out && ./omp_out

omp-10000:
	@echo "OMP Running for N = 10000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=10000 -o omp_out && ./omp_out


mpi-100:
	@echo "MPI Running for N = 100";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=100 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-400:
	@echo "MPI Running for N = 400";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=400 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-1000:
	@echo "MPI Running for N = 1000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=1000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-2000:
	@echo "MPI Running for N = 2000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-5000:
	@echo "MPI Running for N = 5000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=5000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-10000:
	@echo "MPI Running for N = 10000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=10000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-1:
	@echo "Running for 1 Process";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 1 mpi_out

mpi-2:
	@echo "Running for 2 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 2 mpi_out

mpi-3:
	@echo "Running for 3 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 3 mpi_out

mpi-4:
	@echo "Running for 4 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 4 mpi_out

mpi-5:
	@echo "Running for 5 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 5 mpi_out

mpi-6:
	@echo "Running for 6 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 6 mpi_out

mpi-7:
	@echo "Running for 7 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 7 mpi_out

mpi-8:
	@echo "Running for 8 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

clean:
	@rm -f omp_out mpi_out;
