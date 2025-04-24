/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 24 de abril de 2025, 02:50 PM
 */

#include <iostream>
#include <climits>

using namespace std;

const int MAX_N = 501;

int menorCantidadCuadrados(int N) {
    int dp[N];

    dp[0] = 0; // Cero requiere 0 cuadrados

    for (int i = 1; i <= N; i++) {
        dp[i] = INT_MAX;

        for (int j = 1; j * j <= i; j++) {
            int cuadrado = j * j;
            if (dp[i - cuadrado] + 1 < dp[i]) {
                dp[i] = dp[i - cuadrado] + 1;
            }
        }
    }

    return dp[N];
}

int main() {
    int n;
    n = 7;

    int resultado = menorCantidadCuadrados(n);
    cout << "Mínimo número de cuadrados perfectos que suman " << n << " es: " << resultado << endl;

    return 0;
}