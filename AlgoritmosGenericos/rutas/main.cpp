
/* 
 * File:   main.cpp
 * Author: Andrew Max
 *
 * Created on 27 de junio de 2025, 11:03 PM
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#define Tseleccion 0.3 // Parte de la poblacion que se usara para 
#define Pcrossover 0.5
#define Tmutacion 0.5
#define NUM_CIUDADES 5
#define TAM_POBLACION 6
#define NITERACIONES 1000
using namespace std;
int (*gpaq)[NUM_CIUDADES];

bool esAberracion(vector<int> cromosomaAux) {
    // 1. La ruta final debe ser 0
    if (cromosomaAux[NUM_CIUDADES - 1] != 0) //EL ultimo debe ser 0
        return true;


    // 2. No debe haber ciudades repetidas (verificamos usando  búsqueda)
    for (int i = 0; i < cromosomaAux.size(); i++) {
        for (int j = i + 1; j < cromosomaAux.size(); j++) {
            if (cromosomaAux[i] == cromosomaAux[j])
                return true;
        }
    }

    // Por temas del problema todas las transiciones sera posibles

    return false; // No es aberración, es válida
}

void generarPoblacionInicial(vector<vector<int>> &poblacion, int distancias[][NUM_CIUDADES]) {
    int cont = 0;

    while (cont < TAM_POBLACION) {
        vector<int> cromosomaAux;
        for (int i = 0; i < NUM_CIUDADES; i++)
            cromosomaAux.push_back(rand() % 5); //(genera numero del 1 al 4 de forma aleatoria)
        //Verifica que lo creado sea valido
        if (not esAberracion(cromosomaAux)) {
            poblacion.push_back(cromosomaAux);
            cont++;
        }
    }
}

int calcularDistancia(const vector<int> &poblacion, int distancias[][NUM_CIUDADES]) {
    int dis = 0;
    int actual = 0;
    for (int i = 0; i < NUM_CIUDADES; i++) {
        dis += distancias[actual][poblacion[i]];
        actual = poblacion[i];
    }

    return dis;
}

void imprimirPoblacion(const vector<vector<int>> &poblacion, int distancias[][NUM_CIUDADES]) {
    for (const auto& elem : poblacion) {
        cout << 0 <<"  ";
        for (const auto& valor : elem) {
            cout << valor << "  ";
        }
        cout << "fit: " << calcularDistancia(elem, distancias) << endl;
    }
}

void calculaSupervivencia(vector<vector<int>> poblacion,
        vector<int>& supervivencia, int distancias[][NUM_CIUDADES]) {
    vector<double> fitnessValues;
    double sumaFitness = 0.0;

    for (int i = 0; i < poblacion.size(); i++) {
        double dist = calcularDistancia(poblacion[i], distancias);
        double fit = 1.0 / dist; // siempre dist > 0 ya que hay rutas 
        fitnessValues.push_back(fit);
        sumaFitness += fit;
    }

    for (int i = 0; i < fitnessValues.size(); i++) {
        int porcentaje = round(100.0 * fitnessValues[i] / sumaFitness);
        supervivencia.push_back(porcentaje);
    }
}

void cargaProbabilityTable(vector<int> supervivencia, int *probabilityTable) {
    int contador = 0;
    for (int i = 0; i < supervivencia.size(); i++)
        for (int j = 0; j < supervivencia[i]; j++)
            probabilityTable[contador++] = i;
}

void seleccionarPadres(vector<vector<int>> &padres, vector<vector<int>> poblacion,
        int distancias[][NUM_CIUDADES]) {
    int probabilityTable[100];
    for (int i = 0; i < 100; i++) {
        probabilityTable[i] = -1;
    }

    vector<int> supervivencia;
    calculaSupervivencia(poblacion, supervivencia, distancias);
    cargaProbabilityTable(supervivencia, probabilityTable);
    int cantSelecionada = poblacion.size() * Tseleccion;
    for (int i = 0; i < cantSelecionada; i++) {
        int index = rand() % 100; // numero aleatorio del 1 al 99
        //Verifica que la casilla de ruleta tenga un índice válido.
        if (probabilityTable[index]> -1)
            padres.push_back(poblacion[probabilityTable[index]]);
    }
}

void crossover(vector<int> padre, vector<int> madre, vector<int> &hijo) {
    int pos = round(padre.size() * Pcrossover); // aplica crossover entre padres
    for (int i = 0; i < pos; i++) {
        hijo.push_back(padre[i]);
    }
    for (int i = pos; i < madre.size(); i++) {
        hijo.push_back(madre[i]);
    }
}

void crossoverOperator(vector<vector<int>> padres, vector<vector<int>> &poblacion,
        int distancias[][NUM_CIUDADES]) {
    for (int i = 0; i < padres.size(); i++) {
        for (int j = 0; j < padres.size(); j++) {
            if (i != j) {
                vector<int> cromosoma;
                crossover(padres[i], padres[j], cromosoma);
                if (not esAberracion(cromosoma)) {
                    poblacion.push_back(cromosoma);
                }
            }
        }
    }

}
void mutationOperator(vector<vector<int>> padres, vector<vector<int>> &poblacion,
        int distancias[][NUM_CIUDADES]) {
    
    for (const auto& cromoPadre : padres) {
        vector<int> cromosoma = cromoPadre;
        int numMutaciones = round((NUM_CIUDADES - 1) * Tmutacion); // evita mutar el último YA QUE SIEMPRE ES 0

        int cont = 0;
        while (cont < numMutaciones) {
            int i = rand() % (NUM_CIUDADES - 1); // sin tocar el último (que debe ser 0)
            int j = rand() % (NUM_CIUDADES - 1);
            while (i == j) j = rand() % (NUM_CIUDADES - 1); // aseguramos dos distintos
            swap(cromosoma[i], cromosoma[j]);
            cont++;
        }

        if (!esAberracion(cromosoma)) {
            poblacion.push_back(cromosoma);
        }
    }
}

int cambioBase(vector<int> cromosoma) {
    int numero = 0;
    for (int i = 0; i < cromosoma.size(); i++)
        numero += pow(5, i) * cromosoma[i]; //Numero base 5 a decimal
    return numero;
}

void limpiarRedundanciaGenetica(vector<vector<int>> &poblacion,
        int distancias[][NUM_CIUDADES]) {
    map<int, vector<int>> mUnicos;

    for (const auto& elem : poblacion) {
        int numDecimal = cambioBase(elem);
        mUnicos[numDecimal] = elem;
    }
    poblacion.clear();

    for (const pair<const int, vector<int>> &elemento : mUnicos) {
        poblacion.push_back(elemento.second);
    }

}

bool compara(vector<int>a, vector<int>b) {
    return calcularDistancia(a, gpaq) < calcularDistancia(b, gpaq); //Ordena la población de menor a mayor fitness
}

void conservarMasAptos(vector<vector<int>> &poblacion, int distancias[][NUM_CIUDADES]) {

    gpaq = distancias;
    sort(poblacion.begin(), poblacion.end(), compara); //Ordena de mayor a menos

    if (poblacion.size() > TAM_POBLACION) {
        poblacion.erase(poblacion.begin() + TAM_POBLACION, poblacion.end());
    }


}

void muestraMasApto(vector<vector<int>> &poblacion, int distancias[][NUM_CIUDADES]) {
    int mejor = 0;

    int mejorActual = calcularDistancia(poblacion[mejor], distancias);
    cout << endl << "La mejor solucion es: " << mejorActual << "  ";

    cout << 0 <<"  ";
    for (int i = 0; i < poblacion[mejor].size(); i++) {
        cout << poblacion[mejor][i] << "  ";
    }

    cout << endl;
}

void RutasAG(int distancias[][NUM_CIUDADES]) {
    srand(time(NULL));
    int cont = 0;
    vector<vector<int>> poblacion;
    generarPoblacionInicial(poblacion, distancias);

    cout << "Primera Poblacion" << endl;
    imprimirPoblacion(poblacion, distancias);
    cout << "//////////////" << endl;

    do {
        cout << "nuevo" << endl;
        vector<vector<int>> padres;
        // selecciona padres según su fitness (probabilityTable)
        seleccionarPadres(padres, poblacion, distancias);
        // Operadores de variación genética
        crossoverOperator(padres, poblacion, distancias); //Casamiento
        mutationOperator(padres, poblacion, distancias); //MUTACION
        // Elimina individuos repetidos o inválidos
        limpiarRedundanciaGenetica(poblacion, distancias);
        //Selecciona los mejores (NIND)
        conservarMasAptos(poblacion, distancias);
        //Imprime Poblacion de mejores actual
        imprimirPoblacion(poblacion, distancias);
        cout << endl;
        //Muestar la mejor solucion de la muestra (fitness) actual
        muestraMasApto(poblacion, distancias);
        cont++;

    } while (cont != NITERACIONES);


}

int main(int argc, char** argv) {
    int distancias[NUM_CIUDADES][NUM_CIUDADES] = {
        {0, 2, 9, 10, 7},
        {1, 0, 6, 4, 3},
        {15, 7, 0, 8, 3},
        {6, 3, 12, 0, 5},
        {10, 4, 8, 9, 0}
    };
    RutasAG(distancias);




    return 0;
}

