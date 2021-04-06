#include <omp.h>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#define N 1000

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
    cout << "Max threads: " << omp_get_max_threads() << endl;
    cout << "Initializing Random Matrices" << endl;
    static float A[N][N], B[N][N], C[N][N] = {0};
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            A[i][j] = randomFloat();
            B[i][j] = randomFloat();
        }
    // print(A);
    // print(B);
    int timer;
    std::chrono::_V2::system_clock::time_point start, stop;

    start = chrono::high_resolution_clock::now();
    cout << "Multiplying Matrices" << endl;
    multiply(A, B, C);
    stop = chrono::high_resolution_clock::now();
    timer = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
    cout << "\n\tTime Elapsed = " << timer << " ms\n\n";
    // print(C);

    start = chrono::high_resolution_clock::now();
    cout << "Transforming into Upper Triangluar" << endl;
    gaussianElimination(C);
    stop = chrono::high_resolution_clock::now();
    timer = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
    cout << "\n\tTime Elapsed = " << timer << " ms\n\n";
    // print(C);
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
