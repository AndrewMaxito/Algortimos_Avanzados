
/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 11 de abril de 2025, 05:04 PM
 */

#include <iostream>
#include <iomanip>
using namespace std;
int pisos = 5;
int internos = 7;
int MatrizRopa[5][7]={
    {14,11,10,19,14,11, 0},
    {20,11,11,10,15,17,18},
    {15,16,15,16, 0, 0, 0},
    {11, 4,19,12,10, 0, 0},
    {18,12, 0, 0, 0, 0, 0},
};
int MatrizPrecio[5][2]={
    {6,5},
    {7,6},
    {4,8},
    {5,5},
    {2,9},
};

int backTrackMochilero(int pos,int *arr,int pesoBuscado ,int cant){
    if (0 > pesoBuscado)return 0;
    if (mejorSolu>sumaPesos)
    
    
    

    if (backTrackMochilero(pos+1,arr,pesoBuscado-arr[pos],cant)){
        //gaaaaaaaaa no hace nada es para despistar al enemigo ;v
    }else{
        return backTrackMochilero(pos+1,arr,pesoBuscado,cant);
    }
    
    
    
    
    
    
}



int main(int argc, char** argv) {
    int *arr;
    for (int i = 0; i < pisos; i++) {
        int *arr = MatrizRopa[i] ;
        int cant = MatrizRopa[i][0];
        backTrackMochilero(0,arr,50,cant,mejorSolu);
    }

    backTrackMochilero(0);
    
    return 0;
}

