//----------------------------------------------------------------------
#include <iostream>
#include <cmath>
using namespace std;

int arrPesosCarne1[] = {2, 8, 9, 6, 7};
bool usadosGlobal[6] = {};
int arrSolu[6]{};
int totalPedidos = 0;
const int cant = sizeof(arrPesosCarne1) / sizeof(arrPesosCarne1[0]);

void imprimeYMarcarUsados() {
    cout << "Peso de los cortes de cada pedido: {";
    bool primero = true;
    for (int i = 0; i < cant; i++) {
        if (arrSolu[i] != 0) {
            if (!primero) cout << ", ";
            cout << arrSolu[i];
            usadosGlobal[i] = true;  // marcar como usado
            primero = false;
        }
    }
    cout << "}" << endl;

    // limpiar la solución parcial
    for (int i = 0; i < cant; i++) {
        arrSolu[i] = 0;
    }
}

bool valida(int pos, int k) {
    int contador = 0;
    for (int i = 0; i < cant; i++) {
        if (arrSolu[i]) contador++;
    }

    if (contador == 1) return true;

    for (int i = 0; i < cant; i++) {
        if (arrSolu[i] != 0 and i != pos) {
            if (abs(arrPesosCarne1[pos] - arrSolu[i]) <= k) return true;
        }
    }

    return false;
}

bool buscaPedido(int pos, int pesoRestante, int k) {
    if (pesoRestante == 0) {
        imprimeYMarcarUsados();
        totalPedidos++;

        //  Llamamos recursivamente para buscar otro pedido desde cero
        buscaPedido(0, 15, k);  // OJO: usa el valor original del peso

        return true;
    }

    if (pos >= cant or pesoRestante < 0) return false;

    if (!usadosGlobal[pos]) {
        arrSolu[pos] = arrPesosCarne1[pos];

        if (valida(pos, k)) {
            if (buscaPedido(pos + 1, pesoRestante - arrPesosCarne1[pos], k)) {
                return true;
            }
        }

        arrSolu[pos] = 0;
    }

    return buscaPedido(pos + 1, pesoRestante, k);
}

int main() {
    int pesoBuscado = 15;
    int k = 4;

    buscaPedido(0, pesoBuscado, k); // Solo una llamada

    if (totalPedidos == 0) {
        cout << "No se puede atender ningún pedido." << endl;
    } else {
        cout << "Numero de pedidos que se pueden atender de " << pesoBuscado << " kg: " << totalPedidos << endl;
    }

    return 0;
}