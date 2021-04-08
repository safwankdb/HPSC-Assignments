#include <omp.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>

#ifndef N
#define N 1000
#endif

#ifndef TEST
#define TEST 0
#endif

using namespace std;

void print(float M[N][N]);

float randomFloat() {
    static mt19937 generator(42);
    static uniform_real_distribution<double> dist(-2, 2);
    return dist(generator);
}

void multiply(float A[N][N], float B[N][N], float C[N][N]) {
    int i, j, k;
#pragma omp parallel for private(j, k)
    for (i = 0; i < N; i++)
        for (k = 0; k < N; k++)
            for (j = 0; j < N; j++) C[i][j] += A[i][k] * B[k][j];
}

void gaussianElimination(float R[N][N]) {
    float r;
    int i, j, k;
    for (i = 0; i < N; i++) {
#pragma omp parallel for private(r, k)
        for (j = i + 1; j < N; j++) {
            r = R[j][i] / R[i][i];
            for (k = i; k < N; k++) R[j][k] -= r * R[i][k];
        }
    }
}

int main() {
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::milliseconds ms;
    typedef std::chrono::duration<float> fsec;

    static float A[N][N], B[N][N], C[N][N] = {0};
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i][j] = randomFloat();
            B[i][j] = randomFloat();
        }
    // print(A);
    // print(B);
    auto start = Time::now();
    multiply(A, B, C);
    auto stop = Time::now();
    fsec timer1 = stop - start;
#if TEST
    print(C);
#endif
    start = Time::now();
    gaussianElimination(C);
    stop = Time::now();
    fsec timer2 = stop - start;
#if TEST
    print(C);
#endif
    cout << timer1.count() * 1000 << " ms, " << timer2.count() * 1000 << " ms"
         << endl;
}

void print(float M[N][N]) {
    cout << endl;
    cout.setf(ios::fixed);
    for (int i = 0; i < N; i++) {
        cout << '\t';
        for (int j = 0; j < N; j++)
            cout << setw(10) << setprecision(2) << M[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
