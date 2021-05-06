#include <math.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#ifndef N
#define N 4
#endif

#ifndef TEST
#define TEST 0
#endif

#ifndef TPB
#define TPB 1024
#endif

using namespace std;

void print(float* M);

float randomFloat() {
    static mt19937 generator(42);
    static uniform_real_distribution<double> dist(-2, 2);
    return dist(generator);
}

__global__ void multiply(float* A, float* B, float* C) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= N * N) return;
    int i = idx / N, j = idx % N;
    for (int k = 0; k < N; k++) C[i * N + j] += A[i * N + k] * B[k * N + j];
    return;
}

int main() {
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::duration<float> fsec;

    static float A[N * N], B[N * N], C[N * N] = {0};
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i * N + j] = randomFloat();
            B[i * N + j] = randomFloat();
        }

    float *A_dev, *B_dev, *C_dev;
    int mat_size = N * N * sizeof(float);
    int num_blocks = ceil(float(N * N) / TPB);

    cudaMalloc((void**)&A_dev, mat_size);
    cudaMalloc((void**)&B_dev, mat_size);
    cudaMalloc((void**)&C_dev, mat_size);
    
    auto start = Time::now();
    cudaMemcpy(A_dev, A, mat_size, cudaMemcpyHostToDevice);
    cudaMemcpy(B_dev, B, mat_size, cudaMemcpyHostToDevice);

    multiply<<<num_blocks, TPB>>>(A_dev, B_dev, C_dev);
    cudaMemcpy(C, C_dev, mat_size, cudaMemcpyDeviceToHost);

    auto stop = Time::now();
    fsec timer1 = stop - start;
#if TEST
    print(C);
#endif
    // cout << C[N*N-1] << endl;
    cout << timer1.count() * 1000 << " ms" << endl;
}

void print(float* M) {
    cout << endl;
    cout.setf(ios::fixed);
    for (int i = 0; i < N; i++) {
        cout << '\t';
        for (int j = 0; j < N; j++)
            cout << setw(10) << setprecision(2) << M[i * N + j] << " ";
        cout << endl;
    }
    cout << endl;
}
