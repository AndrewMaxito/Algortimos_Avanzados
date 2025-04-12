
/* 
 * File:   main.cpp
 * Author: Jason
 *
 * Created on 11 de abril de 2025, 16:35
 */

#include <iostream>
#include <iomanip>

using namespace std;

#define N 8
#define maxMov 8 //se define la cantidad de movimientos máxima
int movimientos[maxMov][2]; //cada movimiento lleva consigo 2 valores, el cambio en "eje x" y el cambio en "eje y"


//no se puede poner de parámetro (int** tablero) porque eso aplica para cuando "tablero" es memoria dinámica, por lo que se pone tablero[N][N]
void rellenaTablero(int tablero[N][N]){
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            tablero[i][j]=0;
}

void mostrarTablero(int tablero[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++)
            cout<<setw(5)<<right<<tablero[i][j];
        cout<<endl;
    }
}

void generaMovimientos(int movimientos[maxMov][2]){
    //Los movimientos serán en sentido antihorario empezando desde abajo derecha
    movimientos[0][0]=-2;movimientos[0][1]= 1;
    movimientos[1][0]=-1;movimientos[1][1]= 2;
    movimientos[2][0]= 1;movimientos[2][1]= 2;
    movimientos[3][0]= 2;movimientos[3][1]= 1;
    movimientos[4][0]= 2;movimientos[4][1]=-1;
    movimientos[5][0]= 1;movimientos[5][1]=-2;
    movimientos[6][0]=-1;movimientos[6][1]=-2;
    movimientos[7][0]=-2;movimientos[7][1]=-1;
}

int esValido(int tablero[N][N],int x,int y){
    if(x>=0 and y>=0 and x<N and y<N){ //si no se sale de los limites
        if(tablero[x][y]==0) return 1; //si no pase por ahí
    }
    return 0;
}

int buscaSolucion(int tablero[N][N],int x,int y,int mov){
    //devuelve 1 si hay solucion, de lo contrario, devuelve cero
    //mientras trabaja, va colocando los lugares en orden por donde va pasando el caballo
    //caso base
    if(mov>N*N){
        return 1; //éxito
    }
    //recorremos todos los posibles movimientos: (los 8 movimientos)
    for(int i=0;i<maxMov;i++){
        int nx = x + movimientos[i][0]; //si el segundo indice es 0 indica el desplazamiento en x
        int ny = y + movimientos[i][1]; //si el segundo indice es 1 indica el desplazamiento en y
        
        //verificamos si es que se puede hacer el movimiento
        if(esValido(tablero,nx,ny)){
            tablero[nx][ny]=mov; //marco el paso del caballo actual
            if(buscaSolucion(tablero,nx,ny,mov+1)){
                //SE HACE LA RECURSION "ADENTRO" <Esto significa que se entra a un "submundo" en donde si el caballo ya no puede más, saldrá de ahí y seguirá de otra forma, o sea con otro movimiento>
                //si la solucion de este "submundo" es la solución correcta, devolvemos el 1 en el "mundo" exterior
                return 1;
            }
            else{
                //De lo contrario, si este submundo no es la solución correcta, deshacemos el paso:
                tablero[nx][ny]=0;
            }
        }
    }
    //si es que no hay forma de que el caballo termine el recorrido, se devuelve cero
    return 0;
}



//RECORDEMOS QUE <"X" REPRESENTA LA FILA DE LA MATRIZ Y DEL TABLERO> Así como <"Y" REPRESENTA LA COLUMNA DE LA MATRIZ Y DEL TABLERO> Ambos, matriz y tablero, son lo mismo
//por tanto, X es el cambio de fila y Y es el cambio de columna
int main(int argc, char** argv) {
    int tablero[N][N];
    
    generaMovimientos(movimientos);
    rellenaTablero(tablero);
    mostrarTablero(tablero);
    cout<<endl;
    
    
    tablero[0][0]=1; //marcamos cuál queremos que sea el primer paso del caballo, en este caso, será el inicio del tablero (arriba izquierda)
    
    if(buscaSolucion(tablero,0,0,2)){
        cout<<"El caballo pudo recorrer todo el tablero"<<endl;
        mostrarTablero(tablero);
    }
    else{
        cout<<"No hay forma de que el caballo recorra todo el tablero"<<endl;
    }
    
    return 0;
}

