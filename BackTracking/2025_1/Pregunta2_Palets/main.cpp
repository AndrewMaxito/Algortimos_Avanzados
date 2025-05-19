/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 19 de mayo de 2025, 02:36 PM
 */

#include <iostream>
#include <iomanip>
#define N 5
#define M 6
using namespace std;
int tableroSol[N][M]{};
int mov[16][2];
int mov2[8][2];
int mejorSol=-1;

void CargarMovimientos(){
    mov[0][0]= -2;mov[0][1]= -2;
    mov[1][0]= -2;mov[1][1]= -1;
    mov[2][0]= -2;mov[2][1]=  0;
    mov[3][0]= -2;mov[3][1]=  1;
    mov[4][0]= -2;mov[4][1]=  2;
    mov[5][0]= -1;mov[5][1]=  2;
    mov[6][0]=  0;mov[6][1]=  2;
    mov[7][0]=  1;mov[7][1]=  2;
    mov[8][0]=  2;mov[8][1]=  2;
    mov[9][0]=  2;mov[9][1]=  1;
    mov[10][0]= 2;mov[10][1]= 0;
    mov[11][0]= 2;mov[11][1]=-1;
    mov[12][0]= 2;mov[12][1]=-2;
    mov[13][0]= 1;mov[13][1]= -2;
    mov[14][0]= 0;mov[14][1]= -2;
    mov[15][0]= -1;mov[15][1]= -2;
}

void CargarMovimientos2(){
    mov2[0][0]= -1;mov2[0][1]= -1;
    mov2[1][0]= -1;mov2[1][1]=  0;
    mov2[2][0]= -1;mov2[2][1]=  1;
    mov2[3][0]=  0;mov2[3][1]=  1;
    mov2[4][0]=  1;mov2[4][1]=  1;
    mov2[5][0]=  1;mov2[5][1]=  0;
    mov2[6][0]=  1;mov2[6][1]= -1;
    mov2[7][0]=  0;mov2[7][1]= -1;
}

void ImpirmirMati(int matri[][M]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << left<< setw(5) <<matri[i][j];
        }
        cout <<endl;
    }
}
bool EsSaltoValido(int x,int y,int tablero[][M]){
    if(x < N and x >= 0 and y < M and y >= 0 and tablero[x][y]==0){
        if (x==0 and y==0)return false;
        for (int i = 0; i < 8; i++) {
            int nx=x + mov2[i][0], ny = y + mov2[i][1];
            if (nx < N and nx >= 0 and ny < M and ny >= 0 and tablero[nx][ny]!=0){
                return false;
            }
        }
        return true;
    }
    return false;
}
void CopiarInformcion(int tablero[][M]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            tableroSol[i][j] = tablero[i][j];
        }
    }
}


int ColocarPaletsBT(int x,int y,int paletPas,int tablero[][M]){
    
    for (int i = 0; i < 16; i++) {
        int nx=x + mov[i][0], ny = y + mov[i][1];
        if(EsSaltoValido(nx,ny,tablero)){
            tablero[nx][ny]=paletPas+1;
            ColocarPaletsBT(nx,ny,paletPas+1,tablero);
            tablero[nx][ny]=0;
        }
    }
    if (paletPas > mejorSol){
        CopiarInformcion(tablero);
        mejorSol = paletPas; 
    }
}

int main(int argc, char** argv) {
    int tablero[N][M]{};
    CargarMovimientos();
    CargarMovimientos2();
    ImpirmirMati(tablero);
    int paletPas=0;
    //solucion bT
    ColocarPaletsBT(0,0,paletPas,tablero);
    cout <<"La solucion es: Con mejor solucion "<<mejorSol<<endl;
    ImpirmirMati(tableroSol);
    return 0;
}

