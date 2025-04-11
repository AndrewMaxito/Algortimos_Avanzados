#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 20;

char equipos[] = "4592";
int tam = strlen(equipos);
char resultado[MAX];

void backtrack(int index, int resIndex) {
    if (index == tam) {
        resultado[resIndex] = '\0'; // terminar la cadena
        cout << resultado << endl;
        return;
    }

    char grupo[MAX];
    int len = 0;

    for (int i = index; i < tam; i++) {
        grupo[len++] = equipos[i];
        grupo[len] = '\0';

        // Copiar grupo al resultado
        for (int j = 0; j < len; j++) {
            resultado[resIndex + j] = grupo[j];
        }

        int nextIndex = resIndex + len;

        // Agregar espacio si no estamos al final
        if (i < tam - 1) {
            resultado[nextIndex] = ' ';
            backtrack(i + 1, nextIndex + 1);
        } else {
            backtrack(i + 1, nextIndex);
        }
    }
}

int main() {
    backtrack(0, 0);
    return 0;
}
