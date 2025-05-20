
/* 
 * File:   main.cpp
 * Author: Max Bardales Giraldo 20192406
 *
 * Created on 10 de mayo de 2025, 09:08 AM
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TablasReg {
    int id;
    int velocidad;
    int usado;
};

struct TablasSolu {
    int id;
    int velocidad;
    vector<int> idSoluciones;
};

bool compara(TablasReg a,TablasReg b){
    return (a.velocidad > b.velocidad);
}
void ImprimeSolucion(TablasSolu *tablaSolu,int cantDisc){
    cout << "Disco   " <<"Tablas     "<<endl; 
    for (int i = 0; i < cantDisc; i++) {
        cout << tablaSolu[i].id << "       ";
        for (auto elem : tablaSolu[i].idSoluciones) {
            cout << elem << " ";
        }
        cout <<endl;
    }
}
bool comparadis(TablasSolu a ,TablasSolu b){
    return a.velocidad > b.velocidad; //Ordena creciente


}

void BuscarSolucionVoraz(TablasReg *arrTablaDatos, TablasSolu *tablaSolu, 
        int cantDatos,int cantDiscos){
    
    //Ordena de forma Decreciente
    sort(arrTablaDatos, arrTablaDatos+cantDatos, compara);
    for (int i = 0; i < cantDatos; i++) {
        sort(tablaSolu,tablaSolu+cantDiscos,comparadis);
        for (int j = 0; j < cantDiscos; j++) {
            if (tablaSolu[j].velocidad > 0 and tablaSolu[j].velocidad >= arrTablaDatos[i].velocidad){
                tablaSolu[j].idSoluciones.push_back(arrTablaDatos[i].id);
                tablaSolu[j].velocidad -= arrTablaDatos[i].velocidad;
                arrTablaDatos[i].usado = 1;
                break;
            }
        }
    }
    ImprimeSolucion(tablaSolu,cantDiscos);
}


int main(int argc, char** argv) {

    
    TablasSolu tablaSolu[4] = {
        {1,250,{}},
        {2,200,{}},
        {3,200,{}},
        {4,100,{}},
    };

    TablasReg tablaDato[6] = {
        {1, 150,0},
        {2, 100,0},
        {3, 180,0},
        {4, 50 ,0},
        {5, 120,0},
        {6, 10 ,0}
    };
    int cantDatos = sizeof tablaDato/sizeof (tablaDato[0]);
    int cantDiscos = sizeof tablaSolu/sizeof(tablaSolu[0]);
    BuscarSolucionVoraz(tablaDato,tablaSolu,cantDatos,cantDiscos);
    return 0;
}

