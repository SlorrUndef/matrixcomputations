#include <bits/stdc++.h>
#include <mpi.h>
#include "others.h"


using namespace std;

/* Генератор элемента a_i_j по формуле k */
double formula(int n, int k, int i, int j) {
    switch (k) {
        case 1:
            return n - max(i, j) + 1;
        case 2:
            return max(i, j);
        case 3:
            return fabs(i - j);
        case 4:
            return 1.0 / (i + j + 1);
        default:
            cerr << "Wrong k" << endl;
            return -2;
    }
}

void generator(double *a, int n, int k, int rank, int p, const string &filename) {
    int rows;

    if (rank + 1 > n % p) rows = n / p;
    else rows = n / p + 1;

    if (k != 0) {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < n; j++)
                a[i * n + j] = formula(n, k, i, j);
    }
    //TODO input from file
}

void outputArray(double *a, double *x, int n, int m, int rank, int p) {
    MPI_Status status;
    for (int i = 0; i < m; i++) {
        if (rank == 0) {
            if (rank == i % p) {
                for (int j = 0; j < m; j++)
                    printf("%10.3e ", a[i / p * n + j]);
                printf("\n");
            } else {
                MPI_Recv(x, m, MPI_DOUBLE, i % p, 0, MPI_COMM_WORLD, &status);
                for (int j = 0; j < m; j++)
                    printf("%10.3e ", x[j]);
                printf("\n");
            }
        } else if (rank == i % p) {
            for (int j = 0; j < m; j++)
                x[j] = a[i / p * n + j];
            MPI_Send(x, m, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }
}
// TODO residual

