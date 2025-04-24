/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 24 de abril de 2025, 01:24 PM
 */

#include <iostream>
#include <cmath>

using namespace std;

int particionMinimaDiferencia(int A[], int n) {
    int sumaTotal = 0;
    for (int i = 0; i < n; i++) sumaTotal += A[i];

    int objetivo = sumaTotal / 2;

    bool dp[objetivo + 1 ]{};
    dp[0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = objetivo; j >= A[i]; j--) {
            dp[j] = (dp[j] or dp[j - A[i]]);
        }
    }

    // Buscar la suma más cercana a sumaTotal/2
    for (int j = objetivo; j >= 0; j--) {
        if (dp[j]) {
            return abs(sumaTotal - 2*j);
        }
    }

    return sumaTotal; // caso límite (no debería llegar aquí)
}

int main() {
    int A[] = {1, 6, 11, 5};
    int n = sizeof (A) / sizeof (A[0]);

    int resultado = particionMinimaDiferencia(A, n);
    cout << "Mínima diferencia: " << resultado << endl;

    return 0;
}
