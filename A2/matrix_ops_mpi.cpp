#define N 1000
#define MASTER 0
#define UP 8055
#define DOWN 5088 /* slave-slave connection is not required */

#include <mpi.h>

#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

void print(float M[N][N]);

float randomFloat() {
    static mt19937 generator(42);
    static uniform_real_distribution<double> dist(-2, 2);
    return dist(generator);
}

int main(int argc, char **argv) {
    double start, end;
    int i, j, k;
    int numProcs;
    int myProc;
    int rows;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myProc);

    start = MPI_Wtime();

    static float A[N][N], B[N][N], C[N][N] = {{0}}; /* initialize to 0 */
    if (myProc == MASTER) {
        cout << "\nMax threads: " << numProcs << endl;
        cout << "Initializing Random Matrices" << endl;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++) {
                A[i][j] = randomFloat();
                B[i][j] = randomFloat();
            }
        cout << "Multiplying Matrices" << endl;
        int p, block = N / numProcs;
        int numRows[numProcs] = {0};
        if (numProcs > N) {
            block = 1;
            for (i = 0; i < N; i++) numRows[i] = 1;
        } else {
            for (i = 0; i < numProcs; i++) numRows[i] = block;
            numRows[numProcs - 1] += N % numProcs;
        }

        for (p = 1; p < numProcs; p++) { /* send rows to PEs*/
            rows = numRows[p];
            MPI_Send(&rows, 1, MPI_INT, p, DOWN, MPI_COMM_WORLD);
            MPI_Send(&A[p * block][0], rows * N, MPI_FLOAT, p, DOWN,
                     MPI_COMM_WORLD);
            MPI_Send(&B, N * N, MPI_FLOAT, p, DOWN, MPI_COMM_WORLD);
        }

        for (i = 0; i < numRows[0]; i++)
            for (k = 0; k < N; k++)
                for (j = 0; j < N; j++) C[i][j] = C[i][j] + A[i][k] * B[k][j];

        for (p = 1; p < numProcs; p++) { /* receive rows from PEs*/
            rows = numRows[p];
            MPI_Recv(&C[p * block][0], rows * N, MPI_FLOAT, p, UP,
                     MPI_COMM_WORLD, &status);
        }
        end = MPI_Wtime();
        // print(C);
        cout << "\n\tTime Elapsed = " << (end - start) * 1000 << " ms\n\n";
    }

    else {
        MPI_Recv(&rows, 1, MPI_INT, MASTER, DOWN, MPI_COMM_WORLD, &status);
        MPI_Recv(&A, rows * N, MPI_FLOAT, MASTER, DOWN, MPI_COMM_WORLD,
                 &status);
        MPI_Recv(&B, N * N, MPI_FLOAT, MASTER, DOWN, MPI_COMM_WORLD, &status);
        for (i = 0; i < rows; i++)
            for (k = 0; k < N; k++)
                for (j = 0; j < N; j++) C[i][j] = C[i][j] + A[i][k] * B[k][j];
        MPI_Send(&C, rows * N, MPI_FLOAT, MASTER, UP, MPI_COMM_WORLD);
    }

    start = MPI_Wtime();
    float r, R[N];

    for (i = 0; i < N - 1; i++) {
        if (myProc == MASTER) {
            if (i == 0) cout << "Transforming into Upper Triangluar" << endl;
            int M = N - i - 1;
            int p, block = M / numProcs;
            int numRows[numProcs] = {0};
            if (numProcs > M) {
                block = 1;
                for (int l = 0; l < M; l++) numRows[l] = 1;
            } else {
                for (int l = 0; l < numProcs; l++) numRows[l] = block;
                numRows[numProcs - 1] += M % numProcs;
            }

            for (p = 1; p < numProcs; p++) {
                rows = numRows[p];
                MPI_Send(&rows, 1, MPI_INT, p, DOWN, MPI_COMM_WORLD);
                MPI_Send(&C[i][0], N, MPI_FLOAT, p, DOWN, MPI_COMM_WORLD);
                MPI_Send(&C[i + 1 + p * block][0], rows * N, MPI_FLOAT, p, DOWN,
                         MPI_COMM_WORLD);
            }

            for (j = 0; j < numRows[0]; j++) {
                r = C[i + 1 + j][i] / C[i][i];
                for (k = i; k < N; k++) C[j + i + 1][k] -= r * C[i][k];
            }

            for (p = 1; p < numProcs; p++) {
                rows = numRows[p];
                MPI_Recv(&C[i + 1 + p * block][0], rows * N, MPI_FLOAT, p, UP,
                         MPI_COMM_WORLD, &status);
            }
        } else {
            MPI_Recv(&rows, 1, MPI_INT, MASTER, DOWN, MPI_COMM_WORLD, &status);
            MPI_Recv(&R, N, MPI_FLOAT, MASTER, DOWN, MPI_COMM_WORLD, &status);
            MPI_Recv(&C, rows * N, MPI_FLOAT, MASTER, DOWN, MPI_COMM_WORLD,
                     &status);
            for (j = 0; j < rows; j++) {
                r = C[j][i] / R[i];
                for (k = i; k < N; k++) C[j][k] -= r * R[k];
            }
            MPI_Send(&C, rows * N, MPI_FLOAT, MASTER, UP, MPI_COMM_WORLD);
        }
    }
    if (myProc == MASTER) {
        // print(C);
        end = MPI_Wtime();
        cout << "\n\tTime Elapsed = " << (end - start) * 1000 << " ms\n\n";
    }
    MPI_Finalize();
    return 0;
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
