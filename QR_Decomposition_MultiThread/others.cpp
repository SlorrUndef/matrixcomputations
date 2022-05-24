#include <bits/stdc++.h>
#include "others.h"
#include <sys/time.h>

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
            exit(1);
    }
}

void outputArray(int n, int m, int l, double *a) {
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            printf(" %10.3e", a[i * n + j]);
        }
        printf("\n");
    }
}

/* Ввод из файла */
void ffin(double *a, int n, const string &filename) {
    ifstream fin;
    fin.open(filename);
    if (!fin) {
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!fin.eof()) {
                if (!(fin >> a[i * n + j])) {
                    cerr << "Error: file has wrong elements" << endl;
                    exit(1);
                }
            } else {
                cerr << "Error: file has less then n*n elements" << endl;
                exit(1);
            }
        }
    }
    fin.close();
}

/* Генератор матрицы */
void generator(double *a, int n, int k, const string &filename) {
    if (k != 0) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                a[i * n + j] = formula(n, k, i, j);
    } else {
        ffin(a, n, filename);
    }
}
/* Невязка */
double residual(double *a, double *x, int n) {
    int i, j, k;
    double tmp;
    double rezult;

    rezult = 0.0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            tmp = 0.0;
            for (k = 0; k < n; k++)
                tmp += a[i * n + k] * x[k * n + j];
            if (i == j)
                tmp -= 1.0;
            rezult += tmp * tmp;
        }

    return sqrt(rezult);
}


double get_full_time() {
    struct timeval buf;
    gettimeofday(&buf, 0);
    return (double) buf.tv_sec + (double) buf.tv_usec / 1000000.0;
}
