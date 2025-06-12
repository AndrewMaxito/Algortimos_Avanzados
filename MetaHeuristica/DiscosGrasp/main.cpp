
/* 
 * File:   main.cpp
 * Author: Max Bardales
 */
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <algorithm>
#define ITERACIONES 1000000
#define ALFA 0.30

using namespace std;

struct tobjeto{
    int id;
    int rendimiento;
};
struct tresultado{
    int idDisco;
    int idTabla;
};
bool compara(tobjeto a,tobjeto b)
{
    return a.rendimiento > b.rendimiento ; //Ordena de forma decreciente (de mayor a menor )
}
int buscaInd(vector<tobjeto> temTablas,int inf_RCL)
{
    int cont = 0;
    for (auto elmentoTabla : temTablas) {
        if (inf_RCL <= elmentoTabla.rendimiento)
        {
            cont++;
        }else break; //Optimiza la solucion (al estar ordenado el primero en no coincidir es referente de los demas)
    }
    return cont;
}

int calculaCantRCL_inf(vector<tobjeto> objeto)
{
    int beta = objeto[0].rendimiento ;                // Beta Mejor valor actual y umbral superior del rcl
    int tau = objeto.back().rendimiento;              // tau = peor valor actual
    int inf_RCL_objeto  = beta - ALFA*( beta - tau ); // RCL = Umbral inferior para RCL
    int cant_RCL = buscaInd(objeto,inf_RCL_objeto);
    return cant_RCL;
}

void cargaDiscosGRASP(struct tobjeto *tablas, int cantTablas, struct tobjeto* discos, int cantDiscos)
{
    int mejor = -1;
    vector<tresultado> mejorSolucion;
    //Aleatoridiedad
    srand(time(NULL));


    //Iteraciones GRASP
    for (int i = 0; i < ITERACIONES; i++)
    {
        //1. Iniciar Pruebas de aleatoriedad de nueva solucion (Datos por defecto)
        vector<tobjeto> temTablas(tablas, tablas + cantTablas );
        vector<tobjeto> temDiscos(discos, discos + cantDiscos);
        vector<tresultado> solIteracion;
        //Odrednar Discos de mayor a menor por su rendimiento
        sort(temTablas.begin(),temTablas.end(), compara);
        //Escoger Aleatoriamente hasta que se se tenga una solucion o hasta que se haya llenado todos los discos
        
        while (!temTablas.empty())
        { 
            /* Para Las tablas*/
            int cant_RCL_tablas = calculaCantRCL_inf(temTablas);
            int random_index_tablas = rand()%cant_RCL_tablas; //escoje un indece aleatorio del rango RCl
            /*Para los discos */
            //Primero se ordena
            sort(temDiscos.begin(),temDiscos.end(), compara);
            int cant_RCL_discos = calculaCantRCL_inf(temDiscos);
            int random_index_discos = rand()%cant_RCL_discos; //escoje un indece aleatorio del rango RCl

            if (temDiscos[random_index_discos].rendimiento >= temTablas[random_index_tablas].rendimiento)
            {
                temDiscos[random_index_discos].rendimiento -= temTablas[random_index_tablas].rendimiento;
                solIteracion.push_back({temDiscos[random_index_discos].id,temTablas[random_index_tablas].id});
            }
            temTablas.erase(temTablas.begin() + random_index_tablas);
        }
        //Observa cual es el disco con menos espacio
        sort(temDiscos.begin(),temDiscos.end(), compara);
        int residual = temDiscos.back().rendimiento;
        if (residual > mejor)
        {
            mejor = residual;
            mejorSolucion.clear(); //Borra la vieja solucion
            mejorSolucion.insert(mejorSolucion.begin(),solIteracion.begin(),solIteracion.end());
        }
    }

    cout << "Mejor velocidad es:" <<mejor <<endl;
    for (auto elem : mejorSolucion) {
        cout << elem.idDisco <<" "<<elem.idTabla <<endl;
    }      
}


int main(int argc, char const *argv[])
{
    tobjeto tablas[]{
        {1,150},
        {2,100},
        {3,80},
        {4,50},
        {5,120},
        {6,10}
    };
    tobjeto discos[]{
        {1,250},
        {2,200},
        {3,200},
    };
    int cantTablas = sizeof(tablas)/sizeof(tablas[0]);
    int cantDiscos = sizeof(discos)/sizeof(discos[0]); 
    cargaDiscosGRASP(tablas, cantTablas, discos, cantDiscos);
    return 0;
}
