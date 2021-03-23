#include <omp.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#define vf vector<float>
#define vvf vector<vector<float>>

using namespace std;

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
#pragma omp parallel for shared(C) private(i, j, k)
    for (i = 0; i < N; i++)
        for (k = 0; k < N; k++)
            for (j = 0; j < N; j++) C[i][j] += A[i][k] * B[k][j];
    return C;
}

vvf gaussianElimination(vvf &A) {
    vvf R(A);
    float r;
    int n = A.size(), i, j, k;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            r = R[j][i] / R[i][i];
#pragma omp parallel for private(k)
            for (k = i; k < n; k++) R[j][k] -= r * R[i][k];
        }
    }
    return R;
}

int main() {
    const int N = 1000;

    cout << "Initializing Random Matrices" << endl;
    vvf A(N, vf(N, 0)), B(N, vf(N, 0));
    for (vf &row : A) generate(row.begin(), row.end(), randomFloat);
    for (vf &row : B) generate(row.begin(), row.end(), randomFloat);

    cout << "Multiplying Matrices" << endl;
    vvf C = multiply(A, B);
    // print(C);

    cout << "Transforming into Upper Triangluar" << endl;
    vvf U = gaussianElimination(C);
    // print(U);
}
