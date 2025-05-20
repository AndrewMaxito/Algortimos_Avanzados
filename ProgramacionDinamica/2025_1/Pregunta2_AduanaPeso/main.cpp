/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 19 de mayo de 2025, 06:58 PM
 */

#include <iostream>

using namespace std;

void imprimirDP(bool *dp, int n) {
    cout << "Impresion del DP" << endl;
    for (int i = 0; i < n; i++) {
        cout << dp[i];
    }
    cout << endl;
}
int calcularPesoPosibleDP(int *arrValores, int n, int W) {
    bool dp[W + 1]{};
    dp[0] = true; //incial (0 carga)
    int objetivo = W;
    for (int i = 0; i < n; i++) {
        for (int j = objetivo; j >= arrValores[i]; j--) {
            dp[j] = (dp[j] or dp[j - arrValores[i]]);
        }
        if (dp[objetivo] == true) {
            imprimirDP(dp, objetivo + 1);
            return objetivo;
        }
    }
    imprimirDP(dp, objetivo + 1);
    //Busca el valor que cumple
    for (int j = objetivo; j >= 0; j--) {
        if (dp[j] == true) return j;
    }
    return -1; //Solo por comprobar
}

int main(int argc, char** argv) {
    int arrValores[]{7, 2, 5, 5, 10};
    int n = sizeof arrValores / sizeof (arrValores[0]);
    int W=25;
    int valor = calcularPesoPosibleDP(arrValores,n,W);
    if (valor==W){
        cout << "Sí es posible llegar al peso "<< W;
    }else{
        cout << "No es posible llegar al peso "<< W <<
                ". El peso máximo factible es "<<valor;
    }
    return 0;
}

