#include <bits/stdc++.h>
#include <mpi.h>
#include "others.h"
#include "algo.h"

int main(int argc, char **argv) {
    int n = 0, m = 0, k = 0, p = 0, rank = 0;
    double *a, *x;
    double *x1;
    double t;
    int rows;
    int err1 = 0, err2 = 0;
    std::string filename;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc >= 2) {
        switch (argc) {
            case 4:
                n = std::stoi(argv[1]);
                m = std::stoi(argv[2]);
                if (m > n) {
                    std::cerr << "m must be less then n" << std::endl;
                    if (rank == 0) printf("Not correct usage.\n");
                    MPI_Finalize();
                    return -1;
                }
                k = std::stoi(argv[3]);
                break;
            case 5:
                n = std::stoi(argv[1]);
                m = std::stoi(argv[2]);
                if (m > n) {
                    std::cerr << "m must be less then n" << std::endl;
                    if (rank == 0) printf("Not correct usage.\n");
                    MPI_Finalize();
                    return -1;
                }
                k = std::stoi(argv[3]);
                if (k != 0) {
                    std::cerr << "Input from file k must be 0" << std::endl;
                    if (rank == 0) printf("Not correct usage.\n");
                    MPI_Finalize();
                    return -1;
                }
                filename = argv[4];
                break;
            default:
                std::cerr << "Wrong input" << std::endl;
                if (rank == 0) printf("Not correct usage.\n");
                MPI_Finalize();
                return -1;
        }
    } else {
        std::cerr << "Wrong input" << std::endl;
        if (rank == 0) printf("Not correct usage.\n");
        MPI_Finalize();
        return -1;
    }

    if (rank + 1 > n % p) rows = n / p;
    else rows = n / p + 1;
    a = (double *) malloc(rows * n * sizeof(double));
    x = (double *) malloc(rows * n * sizeof(double));
    x1 = (double *) malloc(2 * n * sizeof(double));
    if (!(a && x && x1)) err1 = 1;
    MPI_Allreduce(&err1, &err2, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    if (err2) {
        if (rank == 0) printf("Not enough memory.\n");

        if (a) free(a);
        if (x) free(x);
        if (x1) free(x1);

        MPI_Finalize();

        return -7;
    }

    generator(a, n, k, rank, p, filename);
    if (rank == 0) printf("Matrix A:\n\n");
    outputArray(a, x1, n, m, rank, p);

    MPI_Barrier(MPI_COMM_WORLD);
    t = MPI_Wtime();

    InvMatrix(a, x, x1, n, rank, p);

    MPI_Barrier(MPI_COMM_WORLD);
    t = MPI_Wtime() - t;

    if (rank == 0) printf("\nMatrix A^{-1}:\n");
    outputArray(x, x1, n, m, rank, p);

    printf("%s : residual = %d elapsed = %.2f s = %d n = %d m = %d p = %d\n", argv[0], 100, t, k, n, m, p);
    free(a);
    free(x);
    free(x1);

    MPI_Finalize();
    return 0;
}