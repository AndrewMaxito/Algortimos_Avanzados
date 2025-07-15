

/* 
 * File:   main.cpp
 * Author: Andrew Max
 *
 * Created on 14 de julio de 2025, 12:12 PM
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#define ITERACIONES 1000 // Máximo de repeticiones del GRASP
#define ALFA 0.36          // Parámetro de relajación: 0=voraz, 1=aleatorio
using namespace std;
double MejorMakespan=9999;
struct Orden {
    int idOrden;
    int cantBotellas;
    int prioridad;
    double tiempoProduccion;
};

struct Linea {
    int idLinea;
    vector<int> idOrdenes;
    double totalAcmulado;
};

bool compararOrdenes(Orden a,Orden b){
    return a.tiempoProduccion > b.tiempoProduccion; //Ordena de mayor a menor
}
bool compararLineas(Linea a,Linea b){
    return a.totalAcmulado < b.totalAcmulado; //Ordena de menor a mayor
}

void calcularTiempoProduccionPedido(Orden *ordenes, int cantidadOrdenes){
    double tiempoXOrden = 2 + 1 +1.5 +1.5; 
    for (int i = 0; i < cantidadOrdenes; i++) {
        ordenes[i].tiempoProduccion = tiempoXOrden*ordenes[i].cantBotellas;

    }
}

int ContarValoresPosibles(const vector<Orden> &V_ordenes,int rcl){
    int cont=0;
    for (const auto& elem : V_ordenes) {
        if (elem.tiempoProduccion >= rcl)cont++;
    }
    return cont;
}
double CalcularMakespan(const vector<Linea>&V_lineas){
    double mejor = -1;
    for (const auto& elemLinea : V_lineas) {
        if (mejor < elemLinea.totalAcmulado) mejor = elemLinea.totalAcmulado;
    }
    return mejor;
}
bool compararLineas_idOrden(Linea a,Linea b){
    return a.idLinea <b.idLinea;
}

void cargarLineasProduccion_Grasp(Orden *ordenes,Linea *lineas,int cantLineas,
        int cantOrdenes){
    vector<Linea> V_lineaSol_mejor;
    srand(time(NULL));                                          // Inicializa la aleatoriedad
    
    for (int i = 0; i < ITERACIONES; i++) {
        vector<Orden> V_ordenes(ordenes,ordenes+cantOrdenes);         //Copia los paquetes 
        sort(V_ordenes.begin(),V_ordenes.end(),compararOrdenes);    //Ordena Paquetes
        vector<Linea> V_lineaSol (lineas,lineas+cantLineas);
        
        while (!V_ordenes.empty()) {
            int beta = V_ordenes[0].tiempoProduccion;                          // Mejor valor actual
            int tau = V_ordenes.back().tiempoProduccion;                       // Peor valor actual
            int rcl = beta - ALFA * (beta - tau);            // Umbral para RCL
            int cant_rcl = ContarValoresPosibles(V_ordenes,rcl);
            //Ordenamos las lineas
            sort(V_lineaSol.begin(),V_lineaSol.end(),compararLineas);    //Ordena Lineas
            int randomIndex = rand() % cant_rcl; 
            (V_lineaSol[0].idOrdenes).push_back(V_ordenes[randomIndex].idOrden) ;
            V_lineaSol[0].totalAcmulado += V_ordenes[randomIndex].tiempoProduccion;
            V_ordenes.erase(V_ordenes.begin()+randomIndex);
        }
        double makespanActual = CalcularMakespan(V_lineaSol);
        //Verificamos si es la mejor solucion
        if (MejorMakespan >  makespanActual){
            MejorMakespan = makespanActual;
            V_lineaSol_mejor = V_lineaSol;
        }
    }
    
    sort(V_lineaSol_mejor.begin(),V_lineaSol_mejor.end(),compararLineas_idOrden);    //Ordena Lineas
    //LLenamos la verdadera linea
    for (int i = 0; i < cantLineas; i++) {
        lineas[i].idOrdenes = V_lineaSol_mejor[i].idOrdenes;
        lineas[i].totalAcmulado = V_lineaSol_mejor[i].totalAcmulado;
    }
}


int main(int argc, char** argv) {
    Orden ordenes[]{
        { 1, 103, 2,0},
        { 2, 58 , 1,0},
        { 3, 88 , 3,0},
        { 4, 126, 1,0},
        { 5, 195, 2,0},
        { 6, 90 , 2,0},
        { 7, 54 , 3,0},
        { 8, 195, 1,0},
        { 9, 124, 2,0},
        {10, 113, 3,0},
        {11, 193, 2,0},
        {12, 55 , 1,0},
        {13, 97 , 1,0},
        {14, 97 , 2,0},
        {15, 169, 2,0},
        {16, 50 , 2,0},
        {17, 167, 3,0},
        {18, 74 , 1,0},
        {19, 79 , 2,0},
        {20, 109, 1,0}
    };
    Linea lineas[]{
        {1,{},0},
        {2,{},0},
        {3,{},0},
        {4,{},0},
        {5,{},0},
    
    };
    
    int cantLineas = sizeof (lineas)/sizeof(lineas[0]);
    int cantOrdenes = sizeof (ordenes)/sizeof(ordenes[0]);
    calcularTiempoProduccionPedido(ordenes,cantOrdenes);
    
    cargarLineasProduccion_Grasp(ordenes,lineas,cantLineas,cantOrdenes);
    //Imprimir
    cout << "Mejor Makespan: "<< MejorMakespan <<endl;
    for (int i = 0; i < cantLineas; i++) {
        cout << "Linea "<<lineas[i].idLinea <<": ";
        for (const auto& elem : lineas[i].idOrdenes) {
            cout << elem <<" ";
        }
        cout <<endl;
    }
    return 0;
}

