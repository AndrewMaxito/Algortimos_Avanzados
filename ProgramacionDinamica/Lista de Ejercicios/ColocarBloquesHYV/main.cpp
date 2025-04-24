
/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 24 de abril de 2025, 01:58 PM
 */

#include <iostream>

using namespace std;

int contarFormas(int n) {
    if (n == 0) return 0; //por si n = 0
    
    int dp[n + 1]{};
    
    for (int i = 1; i <= n; i++) {
        if (i < 4) {
            dp[i] = 1; //Existe solo un caso (Horizontal)
        } else{
            if (i == 4){
                dp[i] = 2; // si es 4 Existen dos casos (Horizontales y verticales)
            }else{
                //En caso sea mayor (funcion dinamica)
                dp[i] = dp[i-1] + dp[i-4];
            }
        }
    }
    return dp[n];
}
int main(int argc, char** argv) {
    int n = 6;
    cout << "Para n= "<<n << " Existen " <<contarFormas(n)<<" formas de colocar las tablas";
    
    return 0;
}

