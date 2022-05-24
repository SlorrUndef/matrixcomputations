#include <bits/stdc++.h>
#include "array_generator.h"
#include "array_output.h"
#include "findValues.h"

using namespace std;

int main(int argc, char **argv) {
    int n = 0, m = 0, k = 0;
    double eps, nevyzka1 = 0, nevyazka2 = 0;
    string filename;
    double *a = nullptr, *values = nullptr;
    if (argc >= 2) {
        switch (argc) {
            case 5:
                n = stoi(argv[1]);
                m = stoi(argv[2]);
                eps = stod(argv[3]);
                if (m > n) {
                    cerr << "m must be less then n" << endl;
                    exit(1);
                }
                k = stoi(argv[4]);
                try {
                    a = new double[n * n];
                } catch (std::bad_alloc &ba) {
                    std::cerr << ba.what() << std::endl;
                    return -1;
                }
                generator(a, n, k, filename);
                break;
            case 6:
                n = stoi(argv[1]);
                m = stoi(argv[2]);
                eps = stod(argv[3]);
                if (m > n) {
                    cerr << "m must be less then n" << endl;
                    exit(1);
                }
                k = stoi(argv[4]);
                if (k != 0) {
                    cerr << "Input from file k must be 0" << endl;
                    exit(1);
                }
                filename = argv[5];
                try {
                    a = new double[n * n];
                } catch (std::bad_alloc &ba) {
                    std::cerr << ba.what() << std::endl;
                    return -1;
                }
                generator(a, n, k, filename);
                break;
            default:
                cerr << "Wrong input" << endl;
                exit(1);
        }
    } else {
        cerr << "Wrong input" << endl;
        exit(1);
    }
    cout << '\n' << "A" << '\n' << endl;
    outputArray(n, m, m, a);
    try {
        values = new double[n];
    } catch (std::bad_alloc &ba) {
        std::cerr << ba.what() << std::endl;
        return -1;
    }

    for (int i = 0; i < n; ++i) {
        nevyzka1 -= a[i * n + i];
        for (int j = 0; j < n; ++j)
            nevyazka2 -= a[i * n + j] * a[j * n + i];
    }
    time_t start = clock();
    findValues(a, n, values, eps);
    time_t end = clock();
    double time = (end - start) / (double) CLOCKS_PER_SEC;
    cout << endl;
    cout << endl;
    cout << "eigenvalues:" << endl;
    printVector(n, values);
    for (int i = 0; i < n; ++i) {
        nevyzka1 += values[i];
        nevyazka2 += values[i] * values[i];
    }
    cout << "nevyazka1 = " << nevyzka1 << '\t' << "nevyazka 2 = " << nevyazka2 << endl;
    cout << endl;
    cout << endl;
    cout << "Time : " << time << endl;
    delete[] a;
    delete[] values;
    return 0;
}