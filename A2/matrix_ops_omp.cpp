#include <omp.h>

#include <algorithm>
#include <chrono>
#include <vector>

#include "utils.h"

#define N 1000

vvf multiply(vvf &A, vvf &B) {
    int i, j, k;
    vvf C(N, vf(N, 0));
#pragma omp parallel for private(j, k)
    for (i = 0; i < N; i++)
        for (k = 0; k < N; k++)
            for (j = 0; j < N; j++) C[i][j] += A[i][k] * B[k][j];
    return C;
}

vvf gaussianElimination(vvf &A) {
    vvf R(A);
    float r;
    int n = A.size(), i, j, k;
    for (i = 0; i < n; i++) {
#pragma omp parallel for private(r, k)
        for (j = i + 1; j < n; j++) {
            r = R[j][i] / R[i][i];
            for (k = i; k < n; k++) R[j][k] -= r * R[i][k];
        }
    }
    return R;
}

int main() {
    cout << "Max threads: " << omp_get_max_threads() << endl;
    cout << "Initializing Random Matrices" << endl;
    vvf A(N, vf(N, 0)), B(N, vf(N, 0));
    int i, j;
#pragma omp parallel for private(j)
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
    vvf C = multiply(A, B);
    stop = chrono::high_resolution_clock::now();
    timer = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
    cout << "\n\tTime Elapsed = " << timer << " ms\n\n";
    // print(C);

    start = chrono::high_resolution_clock::now();
    cout << "Transforming into Upper Triangluar" << endl;
    vvf U = gaussianElimination(C);
    stop = chrono::high_resolution_clock::now();
    timer = chrono::duration_cast<chrono::milliseconds>(stop - start).count();
    cout << "\n\tTime Elapsed = " << timer << " ms\n\n";
    // print(U);
}
