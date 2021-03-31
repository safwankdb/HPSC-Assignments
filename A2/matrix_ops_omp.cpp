#include <omp.h>

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#define vf vector<float>
#define vvf vector<vector<float>>

using namespace std;
using namespace std::chrono;

void print(vvf &M) {
    cout << endl;
    cout.setf(ios::fixed);
    for (vf row : M) {
        cout << '\t';
        for (float i : row) cout << setw(10) << setprecision(2) << i << " ";
        cout << endl;
    }
    cout << endl;
    return;
}

float randomFloat() {
    static mt19937 generator(42);
    static uniform_real_distribution<double> dist(-2, 2);
    return dist(generator);
}

vvf multiply(vvf &A, vvf &B) {
    int i, j, k, N = A.size();
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
    const int N = 10000;
    cout << "Initializing Random Matrices" << endl;
    vvf A(N, vf(N, 0)), B(N, vf(N, 0));
    for (vf &row : A) generate(row.begin(), row.end(), randomFloat);
    for (vf &row : B) generate(row.begin(), row.end(), randomFloat);
    // print(A);
    // print(B);
    int time_taken;
    std::chrono::_V2::system_clock::time_point start_time, stop_time;

    start_time = high_resolution_clock::now();
    cout << "Multiplying Matrices" << endl;
    vvf C = multiply(A, B);
    stop_time = high_resolution_clock::now();
    time_taken = duration_cast<milliseconds>(stop_time - start_time).count();
    cout << "\n\tTime Elapsed = " << time_taken << " ms\n\n";
    // print(C);

    start_time = high_resolution_clock::now();
    cout << "Transforming into Upper Triangluar" << endl;
    vvf U = gaussianElimination(C);
    stop_time = high_resolution_clock::now();
    time_taken = duration_cast<milliseconds>(stop_time - start_time).count();
    cout << "\n\tTime Elapsed = " << time_taken << " ms\n\n";
    // print(U);
}
