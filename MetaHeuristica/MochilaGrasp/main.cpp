/* 
 * File:   main.cpp
 * Author: cueva.r (refactorizado por Max Bardales)
 *
 * Refactorización del algoritmo GRASP aplicado al problema de la mochila,
 * incluyendo condiciones de parada anticipadas y mejoras de legibilidad.
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <algorithm>

#define ITERACIONES 100000 // Máximo de repeticiones del GRASP
#define ALFA 0.36          // Parámetro de relajación: 0=voraz, 1=aleatorio

using namespace std;

// Función para ordenar de mayor a menor
bool compara(int a, int b) {
    return a > b;
}

// Cuenta cuántos elementos cumplen que c(x) >= rcl
int cuentaRCL(const vector<int>& paq, int rcl) {
    int cont = 0;
    for (int i = 0; i < paq.size(); i++)
        if (paq[i] >= rcl) cont++;
    return cont;
}

// Algoritmo GRASP aplicado al problema de la mochila
int cargamochila(int *paq, int peso, int n) {
    int mejor = INT_MAX;         // Guarda el menor espacio libre
    vector<int> maxsol;          // Guarda la mejor solución
    srand(time(NULL));           // Inicializa la aleatoriedad
     
    
    //Iteraciones GRASP
    for (int i = 0; i < ITERACIONES; i++) {
        vector<int> paquetes(paq, paq + n);  // Copia de los paquetes
        vector<int> solucion;
        sort(paquetes.begin(), paquetes.end(), compara); // Orden descendente

        int residual = peso;

        //1. Fase de construcción GRASP
        while (!paquetes.empty() and residual > 0) {
            int beta = paquetes[0];                          // Mejor valor actual
            int tau = paquetes.back();                       // Peor valor actual
            int rcl = beta - ALFA * (beta - tau);            // Umbral para RCL

            int cant_rcl = cuentaRCL(paquetes, rcl);         // Tamaño de la RCL
            if (cant_rcl == 0) break;                        // No hay candidatos válidos

            int idx = rand() % cant_rcl;                     // Selección aleatoria en RCL
            int elegido = paquetes[idx];

            if (residual - elegido >= 0) {
                residual -= elegido;
                solucion.push_back(elegido);
            }

            paquetes.erase(paquetes.begin() + idx); // Elimina usado
        }

        //2. Fase de selección de la mejor solución
        if (residual < mejor) {
            mejor = residual;
            maxsol = solucion;

            //Terminamos si logramos mochila exacta
            if (mejor == 0) break;
        }
    }

    return mejor; // Devuelve el mejor residual (espacio libre)
}

// Función principal
int main(int argc, char** argv) {
    int paq[] = {80, 20, 100, 127, 58, 124, 87, 56, 10, 120, 130};
    int peso = 167;
    int n = sizeof(paq) / sizeof(paq[0]);

    cout << "Mejor espacio libre encontrado: " << cargamochila(paq, peso, n) << endl;

    return 0;
}