all: cuda-exp cuda-exp2 clean
cuda-exp: cuda-100 cuda-400 cuda-800 cuda-1000 cuda-2000 cuda-4000 cuda-6000 cuda-8000 cuda-10000
cuda-exp2: cuda-4 cuda-16 cuda-64 cuda-256 cuda-512 cuda-1024

test:
	@nvcc -O3 mm.cu -D N=6 -D TEST=1 -o cuda_out && ./cuda_out

cuda-100:
	@echo "CUDA Running for N = 100";
	@nvcc -O3 mm.cu -D N=100 -o cuda_out && ./cuda_out

cuda-400:
	@echo "CUDA Running for N = 400";
	@nvcc -O3 mm.cu -D N=400 -o cuda_out && ./cuda_out

cuda-800:
	@echo "CUDA Running for N = 800";
	@nvcc -O3 mm.cu -D N=800 -o cuda_out && ./cuda_out

cuda-1000:
	@echo "CUDA Running for N = 1000";
	@nvcc -O3 mm.cu -D N=1000 -o cuda_out && ./cuda_out

cuda-2000:
	@echo "CUDA Running for N = 2000";
	@nvcc -O3 mm.cu -D N=2000 -o cuda_out && ./cuda_out

cuda-4000:
	@echo "CUDA Running for N = 4000";
	@nvcc -O3 mm.cu -D N=4000 -o cuda_out && ./cuda_out

cuda-6000:
	@echo "CUDA Running for N = 6000";
	@nvcc -O3 mm.cu -D N=6000 -o cuda_out && ./cuda_out

cuda-8000:
	@echo "CUDA Running for N = 8000";
	@nvcc -O3 mm.cu -D N=8000 -o cuda_out && ./cuda_out

cuda-10000:
	@echo "CUDA Running for N = 10000";
	@nvcc -O3 mm.cu -D N=10000 -o cuda_out && ./cuda_out

cuda-4:
	@echo "CUDA Running for 4 threads per block";
	@nvcc -O3 mm.cu -D N=2500 -D TPB=4 -o cuda_out && ./cuda_out

cuda-16:
	@echo "CUDA Running for 16 threads per block";
	@nvcc -O3 mm.cu -D N=2500 -D TPB=16 -o cuda_out && ./cuda_out

cuda-64:
	@echo "CUDA Running for 64 threads per block";
	@nvcc -O3 mm.cu -D N=2500 -D TPB=64 -o cuda_out && ./cuda_out

cuda-256:
	@echo "CUDA Running for 256 threads per block";
	@nvcc -O3 mm.cu -D N=2500 -D TPB=256 -o cuda_out && ./cuda_out

cuda-512:
	@echo "CUDA Running for 512 threads per block";
	@nvcc -O3 mm.cu -D N=2500 -D TPB=512 -o cuda_out && ./cuda_out

cuda-1024:
	@echo "CUDA Running for 1024 threads per block";
	@nvcc -O3 mm.cu -D N=2500 -D TPB=1024 -o cuda_out && ./cuda_out

clean:
	@rm -f cuda_out;
