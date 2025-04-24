
/* 
 * File:   main.cpp
 * Author: Andrew Max
 *
 * Created on 24 de abril de 2025, 12:04 PM
 */

#include <iostream>

using namespace std;

bool puedePartirse(int A[], int n) {
    int sumaTotal = 0;

    for (int i = 0; i < n; i++) {
        sumaTotal += A[i];
    }

    // Si la suma total es impar, no se puede dividir en dos partes iguales
    if (sumaTotal % 2 != 0) return false;

    int objetivo = sumaTotal / 2;
    bool dp[objetivo + 1]{};  // todos inicializado en falso
    dp[0] = true; //EL primero es verdadero ya que se considera como un paquete vacio

    for (int i = 0; i < n; i++) {
        for (int j = objetivo; j >= A[i]; j--) {
            dp[j] = (dp[j] or dp[j - A[i]]);
        }
        if (dp[objetivo]==true) return true; //Se encontro la solucion no hace falta buscar mas
    }
    return dp[objetivo];
}

int main() {
    int A1[] = {1, 5, 11, 5};
    int A2[] = {3, 4, 3};
    //Tamaño
    int n1 = sizeof(A1) / sizeof(A1[0]);
    int n2 = sizeof(A2) / sizeof(A2[0]);

    cout << "A1 puede partirse?: " << (puedePartirse(A1, n1) ? "verdadero" : "falso") << endl;
    cout << "A2 puede partirse?: " << (puedePartirse(A2, n2) ? "verdadero" : "falso") << endl;

    return 0;
}
