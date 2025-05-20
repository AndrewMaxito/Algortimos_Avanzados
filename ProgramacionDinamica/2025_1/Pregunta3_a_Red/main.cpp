#include <iostream>
#define N 6
#define INF 1000000

using namespace std;

// Matriz de adyacencia según la imagen proporcionada
int matriz[N][N] = {
    {0, 3, 5, 0, 0, 0},
    {0, 0, 3, 2, 1, 0},
    {0, 0, 0, 2, 3, 0},
    {0, 0, 0, 0, 1, 6},
    {0, 0, 0, 0, 0, 3},
    {0, 0, 0, 0, 0, 0}
};

// Función que calcula e imprime las distancias mínimas desde el nodo 0
int resolverRutasMinimas(int destino) {
    int dp[N],prev[N];

    // Inicializar todas las distancias como infinitas, excepto el nodo 0
    for (int i = 0; i < N; i++) {
        dp[i] = INF;
        prev[i] = -1;
    }
    dp[0] = 0;

    // Programación dinámica sobre el grafo acíclico
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matriz[i][j] > 0 and dp[i] + matriz[i][j] < dp[j]) {//acumulado menor a lo que ya hay
                dp[j] = dp[i] + matriz[i][j];
                prev[j] = i; //Guarda d donde llegó
            }
        }
    }
    // Reconstruir la ruta
    int ruta[N], k = 0, actual = destino;
    while (actual != -1) {
        cout << actual ;
        actual = prev[actual];
        if (actual != -1)cout<<" <- ";
    }
    cout <<endl;
    return dp[5];
}

int main() {
    int destino = 5;
    int valor =resolverRutasMinimas(destino);
    if (valor != INF){
        cout<<"LA distancia minima es "<<valor;
    }
    
    return 0;
}
