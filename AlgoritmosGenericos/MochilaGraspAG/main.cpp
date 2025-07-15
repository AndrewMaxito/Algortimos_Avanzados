#include <iostream>
#include <vector>
#include <ctime>
#include <map>
#include <cmath>
#include <algorithm> // Para sort

using namespace std;
#define NITERACIONES 15
#define TAM_POBLACION 10

#define Tseleccion 0.3 // Parte de la poblacion que se usara para 
#define Pcrossover 0.5
#define Tmutacion 0.5


#define ALFA 0.36
const int NUM_ITEMS = 5;
const int CAPACIDAD_MAXIMA = 10;



// Estructura para representar un ítem

struct Item {
    int id;
    int peso;
    int valor;
    double eficiencia;
};


vector<Item>* gpaq;

bool esAberracion(vector<int> cromosomaAux, vector<Item> paquetes, int peso) {
    int suma = 0;
    for (int i = 0; i < cromosomaAux.size(); i++) {
        suma += paquetes[i].peso * cromosomaAux[i];
    }
    if (suma == 0 or suma > peso){
        return true;
    }
    
    return false;
}

void calcularEficiencia(vector<Item>& paquetes) {
    for (auto& elem : paquetes) {
        elem.eficiencia = (double) elem.valor / elem.peso;
    }
}

bool copararEficiencia(Item a, Item b) {

    return a.eficiencia > b.eficiencia;

}

int cuentaRCL(const vector<Item>& paq, int rcl) {
    int cont = 0;
    for (int i = 0; i < paq.size(); i++)
        if (paq[i].eficiencia >= rcl) cont++;
    return cont;
}

// Genera la población inicial aplicando GRASP (0 y 1)

void generarPoblacionInicial(vector<Item> paquetes, vector<vector<int>> &poblacion) {
    int cont = 0;
    while (cont < TAM_POBLACION) {
        //Paso 1 : crear el auxiliar de los paquetes
        vector<Item> paquetesAux(paquetes.begin(), paquetes.begin() + NUM_ITEMS); // Copia de los paquetes

        // Paso 2: ordenar de mayor a menor eficiencia
        sort(paquetesAux.begin(), paquetesAux.end(), copararEficiencia);

        // Paso 3: construir solución binaria (GRASP)
        vector<int> solucion(NUM_ITEMS, 0);
        int residual = CAPACIDAD_MAXIMA;

        while (!paquetesAux.empty() and residual > 0) {
            int beta = paquetesAux.front().eficiencia; // Mejor valor actual
            int tau = paquetesAux.back().eficiencia; // Peor valor actual
            int rcl = beta - ALFA * (beta - tau); // Umbral para RCL

            int cant_rcl = cuentaRCL(paquetesAux, rcl); // Tamaño de la RCL
            if (cant_rcl == 0) break; // No hay candidatos válidos

            int idx = rand() % cant_rcl; // Selección aleatoria en RCL
            int elegido = paquetesAux[idx].peso;


            //Controla la aberracion
            if (residual - elegido >= 0) {
                residual -= elegido;
                solucion[idx] = 1; //Activa el cromosoma
            }

            paquetesAux.erase(paquetesAux.begin() + idx); // Elimina usado   
        }

        if (not esAberracion(solucion, paquetes,CAPACIDAD_MAXIMA)) {
            poblacion.push_back(solucion);
            cont++;
        }

    }
}

// Imprime cada cromosoma y su valor total

void imprimirPoblacion(vector<Item> paquetes, const vector<vector<int>> &poblacion) {
    cout << "Población generada:\n";
    for (const auto& cromo : poblacion) {
        int pesoTotal = 0, valorTotal = 0;
        double eficienciaTotal;
        for (int i = 0; i < NUM_ITEMS; i++) {
            cout << cromo[i] << " ";
            if (cromo[i] == 1) {
                pesoTotal += paquetes[i].peso;
                valorTotal += paquetes[i].valor;

            }
        }
        eficienciaTotal = valorTotal * 1.0 / pesoTotal;
        cout << " | Peso: " << pesoTotal << ", Valor: " << valorTotal << ", Eficiencia: " << eficienciaTotal << endl;
    }
}

double calculaFitness(vector<int> cromo, vector<Item> paquetes) {
    int valorTotal = 0;
    int pesoTotal = 0;
    for (int i = 0; i < cromo.size(); i++) {
        if (cromo[i] == 1) {
            valorTotal += paquetes[i].valor;
            pesoTotal += paquetes[i].peso;
        }
    }
    //if (pesoTotal > CAPACIDAD_MAXIMA) return 0;  // penalización
    return valorTotal;

}

void calculaSupervivencia(vector<vector<int>> poblacion,
        vector<int>& supervivencia, vector<Item> paquetes) {
    double suma = 0;

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
        vector<vector<int>> poblacion, vector<Item> paquetes, int n, int peso) {

    int probabilityTable[100];
    for (int i = 0; i < 100; i++) {
        probabilityTable[i] = -1;
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
        vector<Item> paquetes, int peso) {
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
        vector<Item> paquetes, int peso) {

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
        vector<Item> paquetes, int peso) {

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

void limpiarRedundanciaGenetica(vector<vector<int>> &poblacion, vector<Item> paquetes) {
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
    return (double) calculaFitness(a, *gpaq) > (double) calculaFitness(b, *gpaq); //Ordena la población de mayor a menor fitness
}

void conservarMasAptos(vector<vector<int>> &poblacion, vector<Item> paquetes) {

    gpaq = &paquetes;
    sort(poblacion.begin(), poblacion.end(), compara); //Ordena de mayor a menos

    if (poblacion.size() > TAM_POBLACION) {
        poblacion.erase(poblacion.begin() + TAM_POBLACION, poblacion.end());
    }

}

int muestraMasApto(vector<vector<int>> &poblacion, vector<Item> paquetes, int peso) {
    int mejor = 0;


    cout << endl << "La mejor solucion es:" << calculaFitness(poblacion[mejor], paquetes) << endl;
    for (int i = 0; i < poblacion[mejor].size(); i++) {
        cout << poblacion[mejor][i] << "  ";
    }
    cout << endl;
    return peso - calculaFitness(poblacion[mejor], paquetes);
}

void mochilaAG_Grasp(vector<Item> & paquetes) {
    int cont = 0;
    vector<vector<int>> poblacion;
    srand(time(NULL));
    generarPoblacionInicial(paquetes, poblacion);
    imprimirPoblacion(paquetes, poblacion);
    cout << "//////////////" << endl;
    do {
        vector<vector<int>> padres;
        // selecciona padres según su fitness (probabilityTable)
        seleccionarPadres(padres, poblacion, paquetes, NUM_ITEMS, CAPACIDAD_MAXIMA);
        // Operadores de variación genética
        crossoverOperator(padres, poblacion, paquetes, CAPACIDAD_MAXIMA); //Casamiento
        inversionOperator(padres, poblacion, paquetes, CAPACIDAD_MAXIMA); //inversion
        mutationOperator(padres, poblacion, paquetes, CAPACIDAD_MAXIMA); //Mutacion
        // Elimina individuos repetidos o inválidos
        limpiarRedundanciaGenetica(poblacion, paquetes);
        //Selecciona los mejores (NIND)
        conservarMasAptos(poblacion, paquetes);
        //Imprime Poblacion de mejores actual
        imprimirPoblacion(paquetes, poblacion);
        cout << endl;
        //Muestar la mejor solucion de la muestra (fitness) actual
        muestraMasApto(poblacion, paquetes, CAPACIDAD_MAXIMA);
        cont++;
    } while (cont != NITERACIONES);


}

int main(int argc, char** argv) {

    // Lista de ítems
    vector<Item> paquetes = {
        {1, 2, 3}, // Ítem 1
        {2, 3, 4}, // Ítem 2
        {3, 4, 5}, // Ítem 3
        {4, 5, 8}, // Ítem 4
        {5, 9, 10} // Ítem 5
    };
    calcularEficiencia(paquetes);
    mochilaAG_Grasp(paquetes);
    return 0;
}
