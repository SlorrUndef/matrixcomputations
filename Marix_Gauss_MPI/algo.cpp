#include <math.h>
#include <mpi.h>

#include "algo.h"

#define eps 1e-100


void InvMatrix(double *a, double *b, double *x, int n, int rank, int p)
{
    int i, j, k;
    int rows;
    int first;
    double tmp;

    if (rank + 1 > n%p) rows = n/p;
    else rows = n/p + 1;

    for (i = 0; i < rows; i++)
        for (j = 0; j < n; j++)
            b[i * n + j] = (rank + p * i == j);

    for (i = 0; i < n; i++)
    {
        if (rank == i%p)
        {
            tmp = 1.0/a[i/p * n + i];
            for (j = i; j < n; j++)
                a[i/p * n + j] *= tmp;
            for (j = 0; j < n; j++)
                b[i/p * n + j] *= tmp;

            if (i == n - 1) continue;

            for (j = i; j < n; j++)
                x[j] = a[i/p * n + j];
            for (j = 0; j < n; j++)
                x[j + n] = b[i/p * n + j];

            MPI_Bcast(x, 2 * n, MPI_DOUBLE, i%p, MPI_COMM_WORLD);
            for (j = i/p + 1; j < rows; j++)
            {
                tmp = a[j * n + i];
                for (k = i; k < n; k++)
                    a[j * n + k] -= tmp * a[i/p * n + k];
                for (k = 0; k < n; k++)
                    b[j * n + k] -= tmp * b[i/p * n + k];
            }
        }
        else
        {
            if (i == n - 1) continue;

            if (rank > i%p) first = i/p;
            else first = i/p + 1;

            MPI_Bcast(x, 2 * n, MPI_DOUBLE, i%p, MPI_COMM_WORLD);
            for (j = first; j < rows; j++)
            {
                tmp = a[j * n + i];
                for (k = i; k < n; k++)
                    a[j * n + k] -= tmp * x[k];
                for (k = 0; k < n; k++)
                    b[j * n + k] -= tmp * x[k + n];
            }
        }
    }

    for (i = n - 1; i >= 1; i--)
    {
        if (rank == i%p)
        {
            MPI_Bcast(b + i/p * n, n, MPI_DOUBLE, i%p, MPI_COMM_WORLD);
            for (j = i/p - 1; j >= 0 ; j--)
                for (k = 0; k < n; k++)
                    b[j * n + k] -= b[i/p * n + k] * a[j * n + i];
        }
        else
        {
            MPI_Bcast(x, n, MPI_DOUBLE, i%p, MPI_COMM_WORLD);

            if (rank < i%p) first = i/p;
            else if (i/p - 1 >= 0) first = i/p - 1;
            else continue;

            for (j = first; j >= 0; j--)
                for (k = 0; k < n; k++)
                    b[j * n + k] -= x[k] * a[j * n + i];
        }
    }
}
