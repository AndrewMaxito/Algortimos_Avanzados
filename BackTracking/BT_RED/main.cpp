#include <iostream>
#define N 6
#define INF 1000000

using namespace std;

// Matriz de adyacencia
int matriz[N][N] = {
    {0, 3, 5, 0, 0, 0},
    {0, 0, 3, 2, 1, 0},
    {0, 0, 0, 2, 3, 0},
    {0, 0, 0, 0, 1, 6},
    {0, 0, 0, 0, 0, 3},
    {0, 0, 0, 0, 0, 0}
};

int mejorTiempo = INF;

// Función backtracking: busca todas las rutas posibles desde nodo actual hasta destino
void buscarRuta(int actual, int destino, int tiempoAcumulado) {
    // Si llegamos al destino, actualizamos mejor tiempo si es menor
    if (actual == destino) {
        if (tiempoAcumulado < mejorTiempo) {
            mejorTiempo = tiempoAcumulado;
        }
        return;
    }

    // Recorrer todos los posibles siguientes nodos
    for (int siguiente = actual + 1; siguiente < N; siguiente++) {
        if (matriz[actual][siguiente] > 0) {
            buscarRuta(siguiente, destino, tiempoAcumulado + matriz[actual][siguiente]);
        }
    }
}

int main() {
    int destino = 5;  // por ejemplo, queremos llegar del nodo 0 al 5

    buscarRuta(0, destino, 0); // empieza en nodo 0 con tiempo acumulado 0

    if (mejorTiempo != INF) {
        cout << "Distancia mínima de 0 a " << destino << " (Backtracking): " << mejorTiempo << endl;
    } else {
        cout << "No existe ruta de 0 a " << destino << endl;
    }

    return 0;
}