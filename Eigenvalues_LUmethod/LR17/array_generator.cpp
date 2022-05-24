#include <bits/stdc++.h>
#include "array_generator.h"

using namespace std;

/* Генератор элемента a_i_j по формуле k */
double formula(int n, int k, int i, int j) {
    switch (k) {
        case 1:
            return n - max(i, j) + 1;
        case 2:
            if(i == j){
                return 2;
            } else if(abs(i-j) == 1){
                return -1;
            } else{
                return 0;
            }
        case 3:
            if(j == n){
                return i;
            } else if (i == n){
                return j;
            } else if (i == j){
                return 1;
            } else{
                return 0;
            }
        case 4:
            return 1.0 / (i + j + 1);
        default:
            cerr << "Wrong k" << endl;
            exit(1);
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