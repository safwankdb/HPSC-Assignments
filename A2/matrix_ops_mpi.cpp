#define MASTER 0
#define UP 420
#define DOWN 666

#ifndef N
#define N 1000
#endif

#ifndef TEST
#define TEST 0
#endif

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
    float start, end, timer1, timer2;
    int i, j, k;
    int numProcs;
    int myProc;
    int rows;
    int starting_row;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myProc);

    start = MPI_Wtime();

    static float A[N][N], B[N][N], C[N][N] = {{0}};
    if (myProc == MASTER) {
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++) {
                A[i][j] = randomFloat();
                B[i][j] = randomFloat();
            }
        starting_row = 0;
        int p, block = N / numProcs;
        int numRows[numProcs] = {0};
        if (numProcs > N) {
            block = 1;
            for (i = 0; i < N; i++) numRows[i] = 1;
        } else {
            for (i = 0; i < numProcs; i++) numRows[i] = block;
            numRows[numProcs - 1] += N % numProcs;
        }

        for (p = 1; p < numProcs; p++) {
            rows = numRows[p];
            MPI_Send(&rows, 1, MPI_INT, p, DOWN, MPI_COMM_WORLD);
            MPI_Send(&A[p * block][0], rows * N, MPI_FLOAT, p, DOWN,
                     MPI_COMM_WORLD);
            MPI_Send(&B, N * N, MPI_FLOAT, p, DOWN, MPI_COMM_WORLD);
        }

        for (i = 0; i < numRows[0]; i++)
            for (k = 0; k < N; k++)
                for (j = 0; j < N; j++) C[i][j] = C[i][j] + A[i][k] * B[k][j];

        for (p = 1; p < numProcs; p++) {
            rows = numRows[p];
            MPI_Recv(&C[p * block][0], rows * N, MPI_FLOAT, p, UP,
                     MPI_COMM_WORLD, &status);
        }
        end = MPI_Wtime();
#if TEST
        print(C);
#endif
        timer1 = (end - start) * 1000;
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
    int M, p, block;
    int numRows[numProcs];
    int rowsToCollect[numProcs];
    int toCollect, pivotBlock;
    bool hasPivotRow;
    for (i = 0; i < N - 1; i++) {
        if (myProc == MASTER) {
            if (i == 0) {
                block = N / numProcs;
                if (numProcs > N) {
                    block = 1;
                    for (int l = 0; l < numProcs; l++) numRows[l] = l < N;
                } else {
                    for (int l = 0; l < numProcs; l++) numRows[l] = block;
                    numRows[numProcs - 1] += N % numProcs;
                }
            }

            for (p = 1; p < numProcs; p++) {
                rows = numRows[p];
                starting_row = p * block;
                if (i < starting_row) {
                    rowsToCollect[p] = rows;
                } else if (starting_row + rows - 1 > i) {
                    rowsToCollect[p] = starting_row + rows - i - 1;
                } else {
                    rowsToCollect[p] = 0;
                }
            }

            for (p = 1; p < numProcs; p++) {
                rows = numRows[p];
                toCollect = rowsToCollect[p];
                MPI_Send(&toCollect, 1, MPI_INT, p, DOWN, MPI_COMM_WORLD);
                if (toCollect > 0)
                    MPI_Send(&C[i][0], N, MPI_FLOAT, p, DOWN, MPI_COMM_WORLD);
            }

            for (j = i + 1; j < numRows[0]; j++) {
                r = C[j][i] / C[i][i];
                for (k = i; k < N; k++) C[j][k] -= r * C[i][k];
            }
            pivotBlock = (i + 1) / numRows[0];
            if (pivotBlock == numProcs) pivotBlock--;

            for (p = 1; p < numProcs; p++) {
                rows = numRows[p];
                toCollect = rowsToCollect[p];
                if (p != pivotBlock) {
                    hasPivotRow = false;
                    MPI_Send(&hasPivotRow, 1, MPI_C_BOOL, p, DOWN,
                             MPI_COMM_WORLD);
                } else {
                    hasPivotRow = true;
                    MPI_Send(&hasPivotRow, 1, MPI_C_BOOL, p, DOWN,
                             MPI_COMM_WORLD);
                    MPI_Recv(&C[i + 1], N, MPI_FLOAT, p, UP, MPI_COMM_WORLD,
                             &status);
                }
            }

        } else {
            MPI_Recv(&toCollect, 1, MPI_INT, MASTER, DOWN, MPI_COMM_WORLD,
                     &status);
            if (toCollect > 0)
                MPI_Recv(&R, N, MPI_FLOAT, MASTER, DOWN, MPI_COMM_WORLD,
                         &status);
            for (j = rows - toCollect; j < rows; j++) {
                r = C[j][i] / R[i];
                for (k = i; k < N; k++) C[j][k] -= r * R[k];
            }
            MPI_Recv(&hasPivotRow, 1, MPI_C_BOOL, MASTER, DOWN, MPI_COMM_WORLD,
                     &status);
            if (hasPivotRow)
                MPI_Send(&C[rows - toCollect], N, MPI_FLOAT, MASTER, UP,
                         MPI_COMM_WORLD);
        }
    }
    if (myProc == MASTER) {
#if TEST
        print(C);
#endif
        end = MPI_Wtime();
        timer2 = (end - start) * 1000;
        cout << timer1 << " ms, " << timer2 << " ms" << endl;
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
