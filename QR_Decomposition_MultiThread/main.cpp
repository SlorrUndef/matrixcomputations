#include <pthread.h>
#include <cstdlib>
#include <bits/stdc++.h>

#include "others.h"
#include "algo.h"


typedef struct {
    int n;
    double *a;
    double *x;
    int rank;
    int total_threads;
} ARGS;

long int thread_time = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Inversion(void *p_arg) {
    ARGS *arg = (ARGS *) p_arg;
    InvMatrix(arg->n, arg->a, arg->x, arg->rank, arg->total_threads);
    return nullptr;
}

int main(int argc, char **argv) {
    int n = 0, m = 0, k = 0, i = 0;
    double *a, *x;
    double t_full;
    int total_threads;
    pthread_t *threads;
    ARGS *args;
    std::string filename;
    if (argc >= 2) {
        switch (argc) {
            case 5:
                n = std::stoi(argv[1]);
                total_threads = std::stoi(argv[2]);
                m = std::stoi(argv[3]);
                if (m > n) {
                    std::cerr << "m must be less then n" << std::endl;
                    exit(1);
                }
                k = std::stoi(argv[4]);
                a = (double *) malloc(n * n * sizeof(double));
                generator(a, n, k, filename);
                break;
            case 6:
                n = std::stoi(argv[1]);
                total_threads = std::stoi(argv[2]);
                m = std::stoi(argv[3]);
                if (m > n) {
                    std::cerr << "m must be less then n" << std::endl;
                    exit(1);
                }
                k = std::stoi(argv[4]);
                if (k != 0) {
                    std::cerr << "Input from file k must be 0" << std::endl;
                    exit(1);
                }
                filename = argv[5];
                a = (double *) malloc(n * n * sizeof(double));
                generator(a, n, k, filename);
                break;
            default:
                std::cerr << "Wrong input" << std::endl;
                exit(1);
        }
    } else {
        std::cerr << "Wrong input" << std::endl;
        exit(1);
    }

    threads = (pthread_t *) malloc(total_threads * sizeof(pthread_t));
    args = (ARGS *) malloc(total_threads * sizeof(ARGS));
    x = (double *) malloc(n * n * sizeof(double));

    if (!(a && x && threads && args)) {
        printf("Not enough memory!\n");

        if (a) free(a);
        if (x) free(x);
        if (threads) free(threads);
        if (args) free(args);

        return -4;
    }
    std::cout << '\n' << "A" << '\n' << std::endl;
    outputArray(n, m, m, a);

    for (i = 0; i < total_threads; i++) {
        args[i].n = n;
        args[i].a = a;
        args[i].x = x;
        args[i].rank = i;
        args[i].total_threads = total_threads;
    }

    t_full = get_full_time();

    for (i = 0; i < total_threads; i++)
        if (pthread_create(threads + i, 0, Inversion, args + i)) {
            printf("Cannot create thread %d!\n", i);

            if (a) free(a);
            if (x) free(x);
            if (threads) free(threads);
            if (args) free(args);

            return -7;
        }

    for (i = 0; i < total_threads; i++)
        if (pthread_join(threads[i], 0)) {
            printf("Cannot wait thread %d!\n", i);

            if (a) free(a);
            if (x) free(x);
            if (threads) free(threads);
            if (args) free(args);

            return -8;
        }

    t_full = get_full_time() - t_full;

    printf("\nA^-1\n");
    outputArray(n, m, m, x);
    generator(a, n, k, filename);
    printf("%s : residual = %e elapsed = %.2f s = %d n = %d m = %d p = %d\n", argv[0], residual(a, x, n), t_full, k, n,
           m, total_threads);
    free(a);
    free(x);
    free(threads);
    free(args);
    return 0;
}