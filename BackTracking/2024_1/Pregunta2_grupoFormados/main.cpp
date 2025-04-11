#include <iostream>
using namespace std;

int arr[4] = {1, 2, 4, 5};
int n = 4;
int solucion[4] = {};   // 0 = espacio antes, 1 = unir al grupo anterior

void imprimir() {
    for (int i = 0; i < n; i++) {
        if (i > 0 && solucion[i] == 0) cout << " "; // espacio si es nuevo grupo
        cout << arr[i];
    }
    cout << endl;
}

void backtrack(int i) {
    if (i == n) {
        imprimir();
        return;
    }

    // Opción 1: unir al grupo anterior (no espacio antes)
    solucion[i] = 1;
    backtrack(i + 1);

    // Opción 2: separar con espacio (nuevo grupo)
    if (i > 0) { // no tiene sentido separar el primer elemento
        solucion[i] = 0;
        backtrack(i + 1);
    }
}

int main() {
    solucion[0] = 1; // el primero siempre empieza sin espacio
    backtrack(1);
    return 0;
}