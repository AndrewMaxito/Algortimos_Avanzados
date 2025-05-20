
/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 19 de mayo de 2025, 06:45 PM
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

int calcularMaxHorasTurnoDP(int *arrValores, int n, int maxTurno) {
    bool dp[maxTurno + 1]{};
    dp[0] = true; //turno incial (0 horas)
    int objetivo = maxTurno;
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
    int arrValores[]{1, 3, 6, 10, 16};
    int maxTurno;
    int n = sizeof arrValores / sizeof (arrValores[0]);

    //Turno mañana 
    maxTurno = 8;
    cout << "Para el turno mañna maximo se pueden emplear " << 
            calcularMaxHorasTurnoDP(arrValores, n, maxTurno) << endl;

    //Turno mañana-tarde 
    maxTurno = 16;
    cout << "Para el turno mañana-tarde maximo se pueden emplear " << 
            calcularMaxHorasTurnoDP(arrValores, n, maxTurno) << endl;

    //Turno mañana-Tarde-noche
    maxTurno = 24;
    cout << "Para el turno mañana-tarde-noche maximo se pueden emplear " << 
            calcularMaxHorasTurnoDP(arrValores, n, maxTurno) << endl;
    return 0;
}

