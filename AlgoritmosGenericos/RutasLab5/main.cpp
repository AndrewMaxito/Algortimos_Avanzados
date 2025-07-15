

/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 14 de julio de 2025, 08:54 PM
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
#define NUMClientes 7
#define TAM_POBLACION 10
#define NITERACIONES 5
using namespace std;
int (*gpaq)[NUMClientes];


using namespace std;
// Revisa si el camino es válido según la matriz de conectividad
bool esAberracion(vector<int> cromosoma, const int matriz[][NUMClientes]) {
    //Ya se puso que la ruta inicial debe ser 0 y la final 0 (Pero igual se debe poner el cromosoma puede cambiar por los operadores crossover por ejemplo)
    if(cromosoma.front() != 0 or cromosoma.back() != 0) return true;
    //Anterirormete ya se tiene controlado que todos los numero seran diferentes (Paso 1: construir una permutación de ciudades (sin repetir))
    
    //Verificar que la ruta sea poible
    for (int i = 0; i < cromosoma.size() - 1; i++) {
        int desde = cromosoma[i];
        int hasta = cromosoma[i + 1];

        if (matriz[desde][hasta] == 0) return true;  // ruta inválida
    }
    return false; // No es aberración, es válida
}

void ImprimeCromosoma(vector<int> cromosoma,const int distancias[][NUMClientes]){
    

        vector<int> rutaActual;
        int distanciaRuta = 0;
        int distanciaTotal = 0;
        int contadorRutas = 1;
        

        for (int j = 0; j < cromosoma.size() - 1; j++) {
            int desde = cromosoma[j];
            int hasta = cromosoma[j + 1];

            rutaActual.push_back(desde);
            distanciaRuta += distancias[desde][hasta];

            if (hasta == 0) {
                rutaActual.push_back(0);  // cierra la ruta

                // Imprimir ruta del repartidor
                cout << "  Repartidor " << contadorRutas << ": ";
                for (int k = 0; k < rutaActual.size(); k++) {
                    cout << rutaActual[k];
                    if (k < rutaActual.size() - 1) cout << " → ";
                }
                cout << " | Distancia: " << distanciaRuta << endl;

                distanciaTotal += distanciaRuta;
                distanciaRuta = 0;
                rutaActual.clear();
                contadorRutas++;
            }
        }

        cout << "  Total: " << distanciaTotal << endl;

};

void imprimirPoblacion(const vector<vector<int>>& poblacion, const int distancias[][NUMClientes]) {
    cout << "======= POBLACIÓN ======="<<endl;

    for (int i = 0; i < poblacion.size(); i++) {
        const vector<int>& cromosoma = poblacion[i];
        cout << "Cromosoma " << (i + 1) << ":"<<endl;
        ImprimeCromosoma(cromosoma,  distancias);
    }
}


// Genera población inicial de rutas válidas
void generarPoblacionInicial(vector<vector<int>>& poblacion, int matriz[][NUMClientes]) {
    int cont = 0;

    while (cont < TAM_POBLACION) {
        vector<int> clientes;

        // Paso 1: crear la lista de clientes (omitimos el depósito 0)
        for (int i = 1; i < NUMClientes; i++) {
            clientes.push_back(i);
        }

        // Paso 2: mezclar aleatoriamente
        random_shuffle(clientes.begin(), clientes.end());
        

        // Paso 3: insertar un 0 aleatorio como separador (no al inicio ni al final)
        int posSeparador = 1 + rand() % (clientes.size() - 1); // posición entre 1 y N-1
        clientes.insert(clientes.begin() + posSeparador, 0);

        
        // Paso 4: agregar depósito al inicio y al final
        clientes.insert(clientes.begin(), 0);
        clientes.push_back(0);
        



        // Paso 5: validar ruta completa
        if (not esAberracion(clientes, matriz)) {
            poblacion.push_back(clientes);
            cont++;
        }
    }
}
int calcularDistancia(const vector<int> &poblacion, int distancias[][NUMClientes]) {
    int dis = 0;
    for (int i = 0; i < poblacion.size() - 1; i++) {
        int desde = poblacion[i];
        int hasta = poblacion[i + 1];
        dis = distancias[desde][hasta];
    }
    return dis;
}

void calculaSupervivencia(vector<vector<int>> poblacion,
        vector<int>& supervivencia, int distancias[][NUMClientes]) {
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
        int distancias[][NUMClientes]) {
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
        int distancias[][NUMClientes]) {
    for (int i = 0; i < padres.size(); i++) {
        for (int j = 0; j < padres.size(); j++) {
            if (i != j) {
                vector<int> cromosoma;
                crossover(padres[i], padres[j], cromosoma);
                if (not esAberracion(cromosoma,distancias)) {
                    poblacion.push_back(cromosoma);
                }
            }
        }
    }

}

void mutationOperator(vector<vector<int>> padres, vector<vector<int>> &poblacion,
        int distancias[][NUMClientes]) {
    
    for (const auto& cromoPadre : padres) {
        vector<int> cromosoma = cromoPadre;
        int numMutaciones = round(cromosoma.size() * Tmutacion); 

        int cont = 0;
        while (cont < numMutaciones) {
            int i = rand() % (cromosoma.size()); 
            int j = rand() % (cromosoma.size());
            while (i == j) j = rand() % (cromosoma.size()); // aseguramos dos distintos
            swap(cromosoma[i], cromosoma[j]);
            cont++;
        }

        if (not esAberracion(cromosoma,distancias)) {
            poblacion.push_back(cromosoma);
        }
    }
}

int cambioBase(vector<int> cromosoma) {
    int numero = 0;
    for (int i = 0; i < cromosoma.size(); i++)
        numero += pow(NUMClientes, i) * cromosoma[i]; //Numero base NUMClientes a decimal
    return numero;
}

void limpiarRedundanciaGenetica(vector<vector<int>> &poblacion,
        int distancias[][NUMClientes]) {
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

void conservarMasAptos(vector<vector<int>> &poblacion, int distancias[][NUMClientes]) {

    gpaq = distancias;
    sort(poblacion.begin(), poblacion.end(), compara); //Ordena de mayor a menos
   
    if (poblacion.size() > TAM_POBLACION) {
        poblacion.erase(poblacion.begin() + TAM_POBLACION, poblacion.end());
    }


}
void muestraMasApto(vector<vector<int>> &poblacion, int distancias[][NUMClientes]) {
    int mejor = 0; //Ya que ya esta ordenado

    int mejorActual = calcularDistancia(poblacion[mejor], distancias);
    cout << endl << "La mejor solucion es: " << mejorActual << "  "<<endl;
    ImprimeCromosoma(poblacion[mejor],distancias);

    cout << endl;
}

void RutasAG(int distancias[][NUMClientes]) {
    srand(time(NULL));
    int cont = 0;
    vector<vector<int>> poblacion;
    generarPoblacionInicial(poblacion, distancias);

    cout << "Primera Poblacion" << endl;
    imprimirPoblacion(poblacion, distancias);
    cout << "//////////////" << endl;
    
    do {
        cout << "/////////////////////"<<endl;
        cout << "Nueva Poblacion" << endl;
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
        cout << "------ Conclusion ------"<<endl;
        //Muestar la mejor solucion de la muestra (fitness) actual
        muestraMasApto(poblacion, distancias);
        cont++;

    } while (cont != NITERACIONES);
}

int main(int argc, char** argv) {
    
    int distancias[NUMClientes][NUMClientes] = {
        {0, 4, 0, 3, 0, 0, 0}, //Puesto A
        {0, 0, 2, 0, 0, 0, 0}, //Cliente 1
        {8, 0, 0, 0, 2, 0, 0}, //Cliente 2
        {0, 0, 0, 0, 6, 0, 0}, //Cliente 3
        {0, 0, 0, 0, 0, 5, 0}, //Cliente 4
        {0, 0, 0, 0, 0, 0, 2}, //Cliente 5
        {3, 0, 0, 0, 0, 0, 0}//Cliente 6
    };
    RutasAG(distancias);

    return 0;
}

