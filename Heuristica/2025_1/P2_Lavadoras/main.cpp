/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Max Bardales Giraldo 20192406
 *
 * Created on 10 de mayo de 2025, 09:52 AM
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

struct Ordenen{
    int id;
    char tipo;//L o S
    int peso;
    double tiempo;
    int asignado;
};

struct Lavadora{
    int id;
    int tiempo;
    vector<int> idOrdenes;
};
void calcularTiempo(Ordenen *ordenes,int cantOrdenes){
    double lavadoXmin = 1.0*(20/5);  //un kilo de ropa demora en ser lavod
    double SecadoXmin = 1.0*(10/5);  //un kilo de topa demora en ser secado
    
    
    for (int i = 0; i < cantOrdenes; i++) {
        if (ordenes[i].tipo == 'L'){
            ordenes[i].tiempo = ordenes[i].peso*lavadoXmin;
        }else{
            ordenes[i].tiempo = ordenes[i].peso*SecadoXmin;
        }
    }
}
bool compara(Lavadora a, Lavadora b){
    return a.tiempo < b.tiempo;
}

void imprimeLavadoras(Lavadora *lavadoras,int cant){
    
    
    cout << "Lavadora "<<"Ordenes asiganadas       "<<"tiempo Total"<<endl;
    for (int i = 0; i < cant; i++) {
        cout << lavadoras[i].id << "          ";
        for (auto elem : lavadoras[i].idOrdenes) {
            cout << elem << " ";
        }
        cout << "               Total :" <<(double)lavadoras[i].tiempo<<endl;
    }

}


void BuscaSolucion(Lavadora *lavadoras,int cantLav,Ordenen *ordenes,int canOrdenes){
    for (int i = 0; i < canOrdenes; i++) {
        sort(lavadoras,lavadoras+5,compara); //Ordena las lavadoras de forma creciente (el primero siempre sera el menor)
        lavadoras[0].tiempo += ordenes[i].tiempo;
        lavadoras[0].idOrdenes.push_back(ordenes[i].id);
        ordenes[i].asignado=1;
    }
}

bool copmpara2(Lavadora a, Lavadora b){
    return a.id < b.id;
}



int main(int argc, char** argv) {
    //Ingreso de Datos
    Ordenen ordenes[20]={
        {1 ,'L',10,0},
        {2 ,'L',10,0},
        {3 ,'S',8 ,0},
        {4 ,'L',15,0},
        {5 ,'S',9 ,0},
        
        {6 ,'S',11,0},
        {7 ,'L',12,0},
        {8 ,'S',15,0},
        {9 ,'L',6 ,0},
        {10,'S',10,0},
        
        {11,'L',8 ,0},
        {12,'S',15,0},
        {13,'L',11,0},
        {14,'L',7 ,0},
        {15,'L',7 ,0},
        
        {16,'S',8 ,0},
        {17,'S',9 ,0},
        {18,'L',11,0},
        {19,'S',12,0},
        {20,'L',15,0},
    };
    
    Lavadora lavadoras[5]{
        {1,0,{}},
        {2,0,{}},
        {3,0,{}},
        {4,0,{}},
        {5,0,{}},
    };
    calcularTiempo(ordenes,20);
 
    BuscaSolucion(lavadoras,5,ordenes,20);
    
    sort(lavadoras,lavadoras+5,copmpara2); //Ordedna otra vez para tenerlo por id
    
    imprimeLavadoras(lavadoras,5);


    

    return 0;
}

