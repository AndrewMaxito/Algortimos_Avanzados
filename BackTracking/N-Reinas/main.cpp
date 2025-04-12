#include <iostream>
#define N 5
using namespace std;
void limpiar(int matriz[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            matriz[i][j] = 0;
        }
    }
}
bool validar(int matriz[N][N],int fila,int col){
    for(int i=0;i<col;i++){
        if(matriz[fila][i]) return 0;
    }
    for(int i=0;i<fila;i++){
        if(matriz[i][col]) return 0;
    }
    for(int i=col+1;i<N;i++){
        if(matriz[fila][i]) return 0;
    }
    for(int i=fila+1;i<N;i++){
        if(matriz[i][col]) return 0;
    }
    
    
    for(int i=fila,j=col;i>=0 and j>=0 ;i--,j--){
        if(matriz[i][j]) return 0;
    }
    for(int i=fila,j=col;i>=0 and j<N ;i--,j++){
        if(matriz[i][j]) return 0;
    }
    for(int i=fila,j=col;i<N and j>=0 ;i++,j--){
        if(matriz[i][j]) return 0;
    }
    for(int i=fila,j=col;i<N and j<N ;i++,j++){
        if(matriz[i][j]) return 0;
    }
    return 1;
}
bool backtraking(int matriz[N][N],int col,int n){
    if(col == n){
        return 1;
    }
    for(int fila=0;fila<n;fila++){
        if(validar(matriz,fila,col)){
            matriz[fila][col] = 1;
            if(backtraking(matriz,col+1,n)){
                return 1;
            }
        }
        matriz[fila][col] = 0;
    }
    
    return 0;
}
int main(int argc, char** argv) {
    int matriz[N][N];
    limpiar(matriz);
    
    if(backtraking(matriz,0,N)){
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                cout<<matriz[i][j]<<" ";
            }
            cout<<endl;
        }
    }else{
        cout<<"No se pudo resolver las N reinas"<<endl;
    }
    
    
    
    return 0;
}

