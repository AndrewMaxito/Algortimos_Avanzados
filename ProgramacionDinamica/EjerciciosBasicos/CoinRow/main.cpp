

/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 20 de abril de 2025, 11:41 AM
 */

#include <iostream>

using namespace std;


const int MAX = 100; // tamaño máximo para las monedas

// Función que calcula la máxima cantidad de dinero posible
int maxMonedas(int c[], int n) {
    //Condiciones basicas parea evitar errores 
    if (n == 0) return 0;
    if (n == 1) return c[0];

    int dp[MAX];
    //Casos base
    dp[0] = c[0];
    dp[1] = max(c[0], c[1]);

    for (int i = 2; i < n; i++) {
        //Relacion de recurrencia
        dp[i] = max(dp[i - 1], dp[i - 2] + c[i]);
    }

    return dp[n - 1];
}



int main(int argc, char** argv) {
    int monedas[] = {5, 1, 2, 10, 6, 2};
    int n = sizeof(monedas) / sizeof(monedas[0]);

    cout << "Máxima cantidad de dinero: " << maxMonedas(monedas, n) << endl;
    

    return 0;
}

