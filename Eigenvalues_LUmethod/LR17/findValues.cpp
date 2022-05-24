#include "findValues.h"
#include <bits/stdc++.h>

/* Страница 107 */
double normA(double *a, int n) {
    double res = 0;
    for (int i = 0; i < n; i++) {
        double preRes = 0;
        for (int j = 0; j < n; j++)
            preRes += fabs(a[i * n + j]);
        res = fmax(res, preRes);
    }
    return res;
}

/* почти треугольный вид методом вращений */
void rotateMatrix(double *a, int n) {
    double norma;
    /* Процесс из книги R = product from i = 1  to n - 1 product from j = i + 1 to n (T_i_j * A)
     * T_i_j матрица эл-го вращения */
    for (int i = 1; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double x = a[i * n + i - 1], y = a[j * n + i - 1];
            if (fabs(x) < 1e-100 && fabs(y) < 1e-100) {
                continue;
            }
            norma = sqrt(x * x + y * y);
            if (fabs(norma) < 1e-100) {
                continue;
            }
            double Cos = x / norma;
            double Sin = -y / norma;

            a[i * n + i - 1] = norma;
            a[j * n + i - 1] = 0;

            /* T_k_l * A = (T_k_l * x_1, T_k_l * x_2,..., T_k_l * x_n)
             *
             * Вычисление матрицы R */
            for (int m = i; m < n; m++) {
                double temp_col, temp_row;
                /* Произведение T_k_l на вектор x_m */
                temp_col = Cos * a[i * n + m] - Sin * a[j * n + m];
                temp_row = Sin * a[i * n + m] + Cos * a[j * n + m];
                a[i * n + m] = temp_col;
                a[j * n + m] = temp_row;
            }

            for (int m = 0; m < n; m++) {
                double temp_col, temp_row;
                temp_col = Cos * a[m * n + i] - Sin * a[m * n + j];
                temp_row = Sin * a[m * n + i] + Cos * a[m * n + j];
                a[m * n + i] = temp_col;
                a[m * n + j] = temp_row;
            }
        }
    }
}

double findShift(double *a, int n, int k) {
    return a[(k - 1) * n + k];
}

void makeShift(double *a, int n, int k, double s) {
    for (int i = 0; i < k; ++i)
        a[i * n + i] -= s;
}

void LR(double *a, int n, int k) {
    for (int i = 1; i < k; ++i) {
        a[i * n + i - 1] = a[i * n + i - 1] / a[(i - 1) * n + i - 1];

        for (int j = i; j < k; ++j)
            a[i * n + j] -= a[i * n + i - 1] * a[(i - 1) * n + j];
    }
}

void RtimesL(double *a, int n, int k) {
    for (int i = 0; i < k; ++i) {
        if (i != 0)
            a[i * n + i - 1] *= a[i * n + i];

        for (int j = i; j < k; ++j)
            a[i * n + j] += a[i * n + j + 1] * a[(j + 1) * n + j];
    }
}

void findValues(double *a, int n, double *values, double eps) {
    double normEps;
    double s;

    normEps = normA(a, n) * eps;

    rotateMatrix(a, n);

    for (int k = n; k > 2; --k)
        while (fabs(a[(k - 1) * n + k - 2]) > normEps) {
            s = findShift(a, n, k);
            makeShift(a, n, k, s);

            LR(a, n, k);
            RtimesL(a, n,k);

            makeShift(a, n, k, -s);
        }
    /*  РЕШАЕМ КВАДРАТНОЕ УРАВНЕНИЕ !!!*/
    if (n > 1)
    {
        normEps = a[0 * n + 0] + a[1 * n + 1];
        s = a[0 * n + 0] * a[1 * n + 1] - a[0 * n + 1] * a[1 * n + 0];
        s = sqrt(normEps * normEps - 4.0 * s);

        a[0 * n + 0] = 0.5 * (normEps + s);
        a[1 * n + 1] = 0.5 * (normEps - s);
    }

    for (int i = 0; i < n; ++i)
        values[i] = a[i * n + i];
}