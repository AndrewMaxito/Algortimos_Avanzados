
#include <iostream>
using namespace std;
#define N 9  
#define M 5

int mov[8][2];
int cont = 0;
#define MAXMOV 20

void cargaMovimientos() {
    mov[0][0]=-1; mov[0][1]=0;
    mov[1][0]=-1; mov[1][1]=1;
    mov[2][0]=0; mov[2][1]=1;
    mov[3][0]=1; mov[3][1]=1;
    mov[4][0]=1; mov[4][1]=0;
    mov[5][0]=1; mov[5][1]=-1;
    mov[6][0]=0; mov[6][1]=-1;
    mov[7][0]=-1;mov[7][1]=-1;
}

void cargaTabla(char matriz[][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matriz[i][j] = '0';
        }
    }
}

void cargaMinas(char a[][M]) {
    a[0][4]='*';
    a[2][2]='*';
    a[4][1]='*';
    a[4][2]='*';
    a[4][4]='*';
    a[5][1]='*';
    a[5][2]='*';
    a[5][4]='*';
    a[6][1]='*';    
    a[6][3]='*';
    a[7][0]='*';
    a[7][1]='*';
    a[7][2]='*';    
    a[7][3]='*';
    a[8][0]='*';
}

int es_valido(char matriz[N][M], int x, int y) {
    if (x < N && y < M && x >= 0 && y >= 0 && matriz[x][y] == '0')
        return 1;
    return 0;
}
void descubre(char mapa[N][M],char solu[N][M],int x,
        int y){
    for(int i=0;i<8;i++){
        int nx=x+mov[i][0];
        int ny=y+mov[i][1];
        if(es_valido(solu,nx,ny)){
            if(mapa[nx][ny]=='*')
                solu[nx][ny]='*';
        }
    }
    
}
void imprime(char mapa[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            cout << mapa[i][j] << " ";
        cout << endl;
    }
}

int generaSol(int x, int y, char paso, char mapa[][M], char solu[][M]) {
    if(cont==MAXMOV) return 1;
    if(x==N-1 and y==M-1){
        imprime(solu);
        cout << endl;
        solu[0][0]='A';
        cont++;
        return 0;
    }
    descubre(mapa,solu,x,y);
    for(int i=0;i<8;i++){
        int nx=x+mov[i][0];
        int ny=y+mov[i][1];
        if(es_valido(solu,nx,ny)){
            solu[nx][ny]=paso+1;
            if(generaSol(nx,ny,paso+1,mapa,solu))
                return 1;
            solu[nx][ny]='0';
        }
        
    }
    return 0;


}

int main(int argc, char** argv) {
    char mapa[N][M], solu[N][M];
    //cargar movimientos
    cargaMovimientos();
    cargaTabla(mapa);
    cargaMinas(mapa);
    cargaTabla(solu);
    imprime(mapa);
    cout <<endl;
    //
    solu[0][0] = 'A';
    //Genera solucion
    generaSol(0, 0, 'A', mapa, solu);
    cout << cont<<endl;


    return 0;
}
