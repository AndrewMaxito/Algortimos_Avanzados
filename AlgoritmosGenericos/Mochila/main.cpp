
/* 
 * File:   main.cpp
 * Author: Andrew Max
 *
 * Created on 27 de junio de 2025, 06:28 PM
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
#define NITERACIONES 1000
#define TAM_POBLACION 10

using namespace std;
int *gpaq;

bool esAberracion(vector<int> cromosomaAux, int *paquetes, int peso) {
    int suma = 0;
    for (int i = 0; i < cromosomaAux.size(); i++) {
        suma += paquetes[i] * cromosomaAux[i];
    }
    return suma > peso;
}

void generarPoblacionInicial(vector<vector<int>> &poblacion, int *paquetes,
        int n, int peso) {
    int cont = 0;
    while (cont < TAM_POBLACION) {
        vector<int> cromosomaAux;
        for (int i = 0; i < n; i++)
            cromosomaAux.push_back(rand() % 2);
        if (not esAberracion(cromosomaAux, paquetes, peso)) {
            poblacion.push_back(cromosomaAux);
            cont++;
        }
    }
}

int calculaFitness(vector<int> cromo, int *paq) {
    int cont = 0;

    for (int i = 0; i < cromo.size(); i++)
        cont += cromo[i] * paq[i];

    return cont;

}

void imprimirPoblacion(vector<vector<int>> poblacion, int *paquetes) {

    //Mejora el rendimiento en compiladores modernos: const auto&
    for (const auto& elem : poblacion) {
        for (const auto& valor : elem) {
            cout << valor << "  ";
        }
        cout << " fo=" << calculaFitness(elem, paquetes) << endl;
    }
}

void calculaSupervivencia(vector<vector<int>> poblacion,
        vector<int>& supervivencia, int *paquetes) {
    int suma = 0;

    for (int i = 0; i < poblacion.size(); i++)
        suma += calculaFitness(poblacion[i], paquetes);
    for (int i = 0; i < poblacion.size(); i++) {
        int fit = round(100 * (double) calculaFitness(poblacion[i], paquetes) / suma);
        supervivencia.push_back(fit);
    }
}

void cargaProbabilityTable(vector<int> supervivencia, int *probabilityTable) {
    int contador = 0;
    for (int i = 0; i < supervivencia.size(); i++)
        for (int j = 0; j < supervivencia[i]; j++)
            probabilityTable[contador++] = i;
}

void seleccionarPadres(vector<vector<int>>&padres,
        vector<vector<int>> poblacion, int *paquetes, int n, int peso) {

    int probabilityTable[100];
    for (int i = 0; i < 100; i++) {
        probabilityTable[i]=-1;
    }

    vector<int> supervivencia;
    calculaSupervivencia(poblacion, supervivencia, paquetes);
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
        int *paquetes, int peso) {
    for (int i = 0; i < padres.size(); i++) {
        for (int j = 0; j < padres.size(); j++) {
            if (i != j) {
                vector<int> cromosoma;
                crossover(padres[i], padres[j], cromosoma);
                if (not esAberracion(cromosoma, paquetes, peso)) {
                    poblacion.push_back(cromosoma);
                }
            }
        }
    }
}

void inversionOperator(vector<vector<int>> padres, vector<vector<int>> &poblacion,
        int *paquetes, int peso) {

    for (const auto &cromoPadre : padres) {
        vector<int> cromosoma;
        for (const auto &bit : cromoPadre) {
            if (bit == 0) {
                cromosoma.push_back(1);
            } else {
                cromosoma.push_back(0);
            }
        }
        if (not esAberracion(cromosoma, paquetes, peso)) {
            poblacion.push_back(cromosoma);
        }
    }
}

void mutationOperator(vector<vector<int>> padres, vector<vector<int>> &poblacion,
        int *paquetes, int peso) {

    int numMuta = round(padres[0].size() * Tmutacion); // aplica mutaciones a los padres
    for (const auto& cromoPadre : padres) {
        vector<int> cromosoma = cromoPadre;
        int cont = 0;
        while (cont < numMuta) {
            int ind = rand() % padres[0].size();
            if (cromoPadre[ind] == 0) {
                cromosoma[ind] = 1;
            } else
                cromosoma[ind] = 0;
            cont++;
        }
        if (not esAberracion(cromosoma, paquetes, peso)) {
            poblacion.push_back(cromosoma);
        }
    }
}

int cambioBase(vector<int> cromosoma) {
    int numero = 0;
    for (int i = 0; i < cromosoma.size(); i++)
        numero += pow(2, i) * cromosoma[i]; //Numero binario a decimal
    return numero;
}

void limpiarRedundanciaGenetica(vector<vector<int>> &poblacion, int *paquetes) {
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
bool compara(vector<int>a,vector<int>b){
    return calculaFitness(a,gpaq) > calculaFitness(b,gpaq); //Ordena la población de mayor a menor fitness
}
void conservarMasAptos(vector<vector<int>> &poblacion, int *paquetes) {
    
    gpaq=paquetes;
    sort(poblacion.begin(),poblacion.end(),compara); //Ordena de mayor a menos
    
    if (poblacion.size() > TAM_POBLACION) {
        poblacion.erase(poblacion.begin()+TAM_POBLACION,poblacion.end());
    }
    
}

int muestraMasApto(vector<vector<int>> &poblacion, int *paquetes, int peso) {
    int mejor=0;
    for(int i=0;i<poblacion.size();i++)
        if(calculaFitness(poblacion[mejor],paquetes)<calculaFitness(poblacion[i],paquetes))
            mejor=i;
    
    cout << endl<<"La mejor solucion es:" << calculaFitness(poblacion[mejor],paquetes)<<endl;
    for(int i=0;i<poblacion[mejor].size();i++){
        cout << poblacion[mejor][i] << "  ";        
    }
    cout << endl;
    return peso-calculaFitness(poblacion[mejor],paquetes);
}

void mochilaAG(int *paquetes, int peso, int n) {
    int cont = 0;
    vector<vector<int>> poblacion;
    srand(time(NULL));
    //Genera la muestra de la poblacion
    generarPoblacionInicial(poblacion, paquetes, n, peso);
    cout << "Primera Poblacion"<<endl;
    imprimirPoblacion(poblacion, paquetes);
    cout<< "//////////////"<<endl;
    do {
        vector<vector<int>> padres;
        // selecciona padres según su fitness (probabilityTable)
        seleccionarPadres(padres, poblacion, paquetes, n, peso);
        // Operadores de variación genética
        crossoverOperator(padres, poblacion, paquetes, peso); //Casamiento
        inversionOperator(padres, poblacion, paquetes, peso); //inversion
        mutationOperator(padres, poblacion, paquetes, peso); //Mutacion
        // Elimina individuos repetidos o inválidos
        limpiarRedundanciaGenetica(poblacion, paquetes);
        //Selecciona los mejores (NIND)
        conservarMasAptos(poblacion, paquetes);
        //Imprime Poblacion de mejores actual
        imprimirPoblacion(poblacion, paquetes);
        cout<<endl;
        //Muestar la mejor solucion de la muestra (fitness) actual
        muestraMasApto(poblacion, paquetes, peso);
        cont++;
    } while (cont != NITERACIONES);
}

int main(int argc, char** argv) {
    int paquetes []{1, 2, 4, 12, 1, 3, 5, 10, 7}; // arreglo con valores/pesos de objetos
    int peso = 35;
    int n = sizeof (paquetes) / sizeof (paquetes[0]);

    mochilaAG(paquetes, peso, n);

    return 0;
}

