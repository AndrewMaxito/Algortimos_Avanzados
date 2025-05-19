

/* 
 * File:   main.cpp
 * Author: andre
 *
 * Created on 19 de mayo de 2025, 02:10 PM
 */

#include <iostream>
#include <iomanip>
#define N 8
using namespace std;
int tablero[N][N];
int mov[8][2];


void CargarMovimientos(){
    mov[0][0]= -1;mov[0][1]= -1;
    mov[1][0]= -1;mov[1][1]=  0;
    mov[2][0]= -1;mov[2][1]=  1;
    mov[3][0]=  0;mov[3][1]=  1;
    mov[4][0]=  1;mov[4][1]=  1;
    mov[5][0]=  1;mov[5][1]=  0;
    mov[6][0]=  1;mov[6][1]= -1;
    mov[7][0]=  0;mov[7][1]= -1;
}
void CargarMatri(int matri[][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matri[i][j]=0;
        }
    }
}
bool EsValido(int nx,int ny,int solu[][N]){
    if(nx < N and nx >= 0 and ny < N and ny >= 0 and solu[nx][ny]==0){
        return true;
    }
    return false;
}
void ImpirmirMati(int matri[][N]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << left<< setw(5) <<matri[i][j];
        }
        cout <<endl;
    }
}

int  CaminoReyBK(int x,int y,int paso,int solu[][N]){
    if (paso==64){
        ImpirmirMati(solu);
        return 1;
    }
    
    for (int i = 0; i < 8; i++) {
        
        int nx=x + mov[i][0], ny = y + mov[i][1];
        
        if (EsValido(nx,ny,solu)){
            
            solu[nx][ny]=paso+1;
            if(CaminoReyBK(nx,ny,paso+1,solu)){
                return 1;
            }else{
                solu[nx][ny]=0;
            }
        }
    }
    return 0;
}

int main(int argc, char** argv) {
    int solu[N][N];
    CargarMovimientos();
    CargarMatri(tablero);
    CargarMatri(solu);
    ImpirmirMati(solu);
    cout <<endl;
    
    //BT
    //Posicion inicial
    int x0=3,y0=3,paso=1;
    solu[x0][y0] = paso;
    CaminoReyBK(x0,y0,paso,solu);
    return 0;
}

