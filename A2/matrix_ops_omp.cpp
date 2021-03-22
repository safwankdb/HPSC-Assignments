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
    for (auto row : M) {
        cout << '\t';
        for (auto i : row) cout << setprecision(3) << i << " ";
        cout << endl;
    }
    cout << endl;
    return;
}

float randomFloat() {
    static mt19937 generator(42);
    static uniform_real_distribution<double> dist(0, 1);
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
    for (int i = 0; i < N; i++) {
        generate(A[i].begin(), A[i].end(), randomFloat);
        generate(B[i].begin(), B[i].end(), randomFloat);
    }

    cout << "Multiplying" << endl;
    vvf C = multiply(A, B);
    // print(C);

    cout << "Transforming into Upper Triangluar" << endl;
    vvf U = gaussianElimination(C);
    // print(U);
}
