all: omp-exp mpi-exp mpi-exp2 omp-exp2 clean
omp-exp: omp-100 omp-400 omp-800 omp-1000 omp-2000 omp-4000 omp-6000 omp-8000 omp-10000
mpi-exp: mpi-100 mpi-400 mpi-800 mpi-1000 mpi-2000 mpi-4000 mpi-6000 mpi-8000 mpi-10000
mpi-exp2: mpi-2 mpi-3 mpi-4 mpi-5 mpi-6 mpi-7 mpi-8
omp-exp2: omp-2 omp-3 omp-4 omp-5 omp-6 omp-7 omp-8

test:
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=6 -D TEST=1 -o omp_out && ./omp_out
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=6 -D TEST=1 -o mpi_out && mpirun --use-hwthread-cpus -v -np 8 mpi_out

omp-100:
	@echo "OMP Running for N = 100";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=100 -o omp_out && ./omp_out

omp-400:
	@echo "OMP Running for N = 400";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=400 -o omp_out && ./omp_out

omp-800:
	@echo "OMP Running for N = 800";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=800 -o omp_out && ./omp_out

omp-1000:
	@echo "OMP Running for N = 1000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=1000 -o omp_out && ./omp_out

omp-2000:
	@echo "OMP Running for N = 2000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2000 -o omp_out && ./omp_out

omp-4000:
	@echo "OMP Running for N = 4000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=4000 -o omp_out && ./omp_out

omp-6000:
	@echo "OMP Running for N = 6000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=6000 -o omp_out && ./omp_out

omp-8000:
	@echo "OMP Running for N = 8000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=8000 -o omp_out && ./omp_out

omp-10000:
	@echo "OMP Running for N = 10000";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=10000 -o omp_out && ./omp_out


mpi-100:
	@echo "MPI Running for N = 100";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=100 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-400:
	@echo "MPI Running for N = 400";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=400 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-800:
	@echo "MPI Running for N = 800";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=800 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-1000:
	@echo "MPI Running for N = 1000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=1000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-2000:
	@echo "MPI Running for N = 2000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-4000:
	@echo "MPI Running for N = 4000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=4000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-6000:
	@echo "MPI Running for N = 6000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=6000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-8000:
	@echo "MPI Running for N = 8000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=8000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

mpi-10000:
	@echo "MPI Running for N = 10000";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=10000 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

omp-2:
	@echo "OMP Running for 2 Processes";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2500 -D THREADS=2 -o omp_out && ./omp_out

omp-3:
	@echo "OMP Running for 3 Processes";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2500 -D THREADS=3 -o omp_out && ./omp_out

omp-4:
	@echo "OMP Running for 4 Processes";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2500 -D THREADS=4 -o omp_out && ./omp_out

omp-5:
	@echo "OMP Running for 5 Processes";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2500 -D THREADS=5 -o omp_out && ./omp_out

omp-6:
	@echo "OMP Running for 6 Processes";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2500 -D THREADS=6 -o omp_out && ./omp_out

omp-7:
	@echo "OMP Running for 7 Processes";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2500 -D THREADS=7 -o omp_out && ./omp_out

omp-8:
	@echo "OMP Running for 8 Processes";
	@g++ -O3 -fopenmp matrix_ops_omp.cpp -D N=2500 -D THREADS=8 -o omp_out && ./omp_out

mpi-2:
	@echo "MPI Running for 2 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 2 mpi_out

mpi-3:
	@echo "MPI Running for 3 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 3 mpi_out

mpi-4:
	@echo "MPI Running for 4 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 4 mpi_out

mpi-5:
	@echo "MPI Running for 5 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 5 mpi_out

mpi-6:
	@echo "MPI Running for 6 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 6 mpi_out

mpi-7:
	@echo "MPI Running for 7 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 7 mpi_out

mpi-8:
	@echo "MPI Running for 8 Processes";
	@mpic++ matrix_ops_mpi.cpp -O3 -D N=2500 -o mpi_out && mpirun --use-hwthread-cpus -np 8 mpi_out

clean:
	@rm -f omp_out mpi_out;
