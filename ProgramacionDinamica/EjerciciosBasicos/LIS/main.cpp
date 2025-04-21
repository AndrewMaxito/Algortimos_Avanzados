
/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 20 de abril de 2025, 12:05 PM
 */


#include <iostream>
using namespace std;

const int MAX = 100;  // tamaño máximo permitido

int LIS(int X[], int n) {
    int dp[MAX];

    // Paso 3: cada elemento empieza con longitud 1
    for (int i = 0; i < n; i++)
        dp[i] = 1;

    // Paso 4: construir dp[i] usando subproblemas anteriores
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (X[j] < X[i]) {
                //Relacion de recurrencia
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    // Tomar el máximo entre todos los dp[i]
    int maxLIS = 0;
    for (int i = 0; i < n; i++)
        maxLIS = max(maxLIS, dp[i]);

    return maxLIS;
}

int main(int argc, char** argv) {
    int X[] = {-7, 10, 3, 2, 1};
    int n = sizeof(X) / sizeof(X[0]);

    cout << "Longitud de la subsecuencia creciente más larga: " << LIS(X, n) << endl;

    return 0;
}
