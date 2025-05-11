/* 
 * File:   main.cpp
 * Author: Andrew Max B.
 *
 * Created on 9 de mayo de 2025, 01:49 PM
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Proyecto{
    int id;
    int costo;
    int ganancia;
    int beneficio;
    vector<int> predecesores;
};
int buscaPos(Proyecto *arrProyectos,int ind,int tam){
    for (int i = 0; i < tam; i++) {
        if (arrProyectos[i].id == ind)return i;
    }
}
//Comparador para decreciente ya que es boraz
bool compara(Proyecto a, Proyecto b){ 
    double indicadorA = 1.0*(a.beneficio * a.ganancia)/a.costo;
    double indicadorB = 1.0*(b.beneficio * b.ganancia)/b.costo;
    
    return indicadorA > indicadorB;
}
void imprimirArrProyectos(Proyecto *arrProyectos,int tam){
    for (int i = 0; i < tam; i++) {
        double indicador = 1.0*(arrProyectos[i].beneficio * arrProyectos[i].ganancia)/arrProyectos[i].costo;
        cout << arrProyectos[i].id<<" "<<indicador<< endl;
    }
}
int verificarPredecesores(Proyecto *arrProyectos,int pos,
        vector<bool> &arrUsados,int n){
    int posReal =buscaPos(arrProyectos,pos,n);
    int acumulado = arrProyectos[posReal].costo;
    arrUsados[posReal] = true;
    if (arrProyectos[posReal].predecesores.empty()){
        return arrProyectos[posReal].costo; //si no requiere predecesores ***MArcar como  usado
    }
    int tam = arrProyectos[posReal].predecesores.size();
    for (int i = 0; i < tam; i++) {
        int idPrede = arrProyectos[posReal].predecesores[i];
        int posRealPrede = buscaPos(arrProyectos,idPrede,n);
        if (arrUsados[posRealPrede]==false){
            acumulado += verificarPredecesores(arrProyectos,idPrede,arrUsados,n);
            arrUsados[posRealPrede]=true;
        }
    }
    return acumulado;
}

int selecciona(Proyecto *arrProyectos,int n,int P){
    int presumuetosResto = P;
    int gananciaTotal=0;
    vector<bool> arrUsados(n,false);
    //Se ordena de manera decreciente para que los primero sean los mas altos
    sort(arrProyectos,arrProyectos + n,compara);
    //Impresion de prueba
    imprimirArrProyectos(arrProyectos,n);
    
    for (int i = 0; i < n; i++) {
        vector<bool> arrUsadosAux = arrUsados;
        int gananciaAux=0;
        if (arrUsados[i]==false ){

            int totalActual = verificarPredecesores(arrProyectos,arrProyectos[i].id,arrUsadosAux,n);
            if (totalActual <= presumuetosResto){
                presumuetosResto -= totalActual;
                arrUsados = arrUsadosAux;
                if (presumuetosResto == 0)return gananciaTotal;//Se Metio todo
            }
        }
    } 
    cout <<"Verificar "<<endl;
    for (int i = 0; i < n; i++) {
        cout<<arrUsados[i]<<"  ";
        if (arrUsados[i] == true){
            gananciaTotal += arrProyectos[i].ganancia; 
        }
    }
    return gananciaTotal;
}
int main(int argc, char** argv) {
    Proyecto arrProyectos[]={
        {1,80 ,150,2,{}},
        {2,20 ,80 ,5,{4}},
        {3,100,300,1,{1,2}},
        {4,100,150,4,{}},
        {5,50 ,80 ,2,{}},
        {6,10 ,50 ,1,{2}},
        {7,50 ,120,2,{6}},
        {8,50 ,150,5,{6}}
    };
    int n=sizeof(arrProyectos)/sizeof(arrProyectos[0]);
    int P=250;
    cout << "Ganancia Total "<< selecciona(arrProyectos,n,P);
    
    return 0;
}

