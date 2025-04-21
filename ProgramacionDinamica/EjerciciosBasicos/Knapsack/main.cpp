
/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 20 de abril de 2025, 02:22 PM
 */

#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 100; // máximo número de objetos
const int MAX_W = 1000; // máxima capacidad de la mochila

int knapsack(int n, int W, int w[], int v[]) {
    int dp[MAX_N + 1][MAX_W + 1];

    // Paso 3: inicializar la primera fila y columna
    for (int i = 0; i <= n; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= W; j++)
        dp[0][j] = 0;

    // Paso 4: construir la tabla
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (w[i - 1] > j) {
                dp[i][j] = dp[i - 1][j]; // no cabe
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
            }
        }
    }

    return dp[n][W]; // resultado final
}

int main(int argc, char** argv) {
    int w[] = {4, 2, 3, 1};     // pesos
    int v[] = {10, 4, 7, 2};    // valores
    int n = sizeof(w) / sizeof(w[0]);
    int W = 5;                  // capacidad de la mochila

    cout << "Máximo valor que se puede llevar: " << knapsack(n, W, w, v) << endl;
    return 0;
}