#include "array_output.h"
#include <bits/stdc++.h>

void outputArray(int n, int m, int l, double *a) {
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            printf(" %10.3e", a[i * n + j]);
        }
        printf("\n");
    }
}

void printVector(int s, double* x)
{
    for (int i = 0; i < s; ++i)
        printf("%10.3e ", x[i]);
    printf("\n");
}
