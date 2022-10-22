#include <cmath>
#include <iostream>
#include "Random64.h"

const int Lx=1024; //1024
const double p=0.5; //probabilidad de voltear los contenidos i.e. las velocidades

const int Q=2; //cantidad de direcciones en las que se puede mover
//-------Clase LatticeGas----------

class LatticeGas{
    private:
        int n[Lx][Q];//Matriz de autómatas
        int nnew[Lx][Q];//usamos dos copias para paralelismo
        int V[Q];//Matriz de Direcciones. i=0 (moverse a la derecha), i=1(moverse a la izquierda)
    public:
        LatticeGas(void);
        void Borrese(void); //Borra todo el lattice
        //Pasamos por Referencia porque se mantendrá siempre el mismo generador
        void Inicie(int N, double mu,  double sigma, Crandom & ran64);
        void Show(void);
        void Colisione(Crandom & ran64);
        void Adveccione(void);
        //obtenemos la cantidad de particulas
        double rho(int ix){return n[ix][0] + n[ix][1];}//inline
        double Varianza(void);
        void GrafiqueRho(void);
};
LatticeGas::LatticeGas(void){
    V[0]=1; V[1]=-1;
}
void LatticeGas::Borrese(void){
    for(int ix=0; ix<Lx; ix++){
        for(int i=0; i<Q; i++){
            n[ix][i]=nnew[ix][i]=0;
        }
    }
}
//esto inicia las celdas, solo pone bolas en las celdas si están vacias
//, cada celda incia con 1 o 0 bolas.
void LatticeGas::Inicie(int N ,double mu,  double sigma, Crandom & ran64){
    int ix, i;
    while(N>0){
        ix=(int) ran64.gauss(mu, sigma); //escoger una celda al azar
        if(ix<0){ix=0;}//corrección de bordes
        if(ix>Lx-1){ix=Lx-1;}
        i = (int) Q*ran64.r(); //escoger dirección al azar
        if(n[ix][i]==0){ //en caso de que la celda esté vacia
            n[ix][i]=1; //pongo una bola ahí y decresco N
            N--;}
    }
}

void LatticeGas::Show(void){
    for (int i=0; i<Q;i++){
        for (int ix=0; ix<Lx; ix++ ){
            std::cout << n[ix][i];
        }
        std::cout << std::endl;
    }
    std::cout <<std::endl;
}
void LatticeGas::GrafiqueRho(void){
    for (int ix=0; ix<Lx; ix++)
        std::cout << ix << " " << rho(ix) << std::endl;
}
//esta es la parte del coin flip i.e. actualización de velocidades
void LatticeGas::Colisione(Crandom & ran64){
//para cada celda
    for (int ix=0;ix<Lx;ix++){//para cada celda}
        if(ran64.r()>p)// Genero un número al azar, y si es mayor que p volteo
        {
            nnew[ix][0]=n[ix][1]; //intercambio de contenidos
            nnew[ix][1]=n[ix][0];
        }
        else{
            nnew[ix][0]=n[ix][0];
            nnew[ix][1]=n[ix][1];
        }

    }
}
void LatticeGas::Adveccione(void){
        for(int ix=0; ix<Lx;ix++)
            for(int i=0; i<Q; i++)
                n[(ix+V[i]+Lx)%Lx][i]=nnew[ix][i];
    }
//Calculo de la varianza en la posición de las partículas
double LatticeGas::Varianza(void){
  int ix; double N,Xprom,Sigma2;
  //Calcular N
  for(N=0,ix=0;ix<Lx;ix++)
    N+=rho(ix);
  //Calcular Xprom
  for(Xprom=0,ix=0;ix<Lx;ix++)
    Xprom+=ix*rho(ix);
  Xprom/=N;
  //Calcular Sigma2
  for(Sigma2=0,ix=0;ix<Lx;ix++)
    Sigma2+=pow(ix-Xprom,2.0)*rho(ix);
  Sigma2/=(N-1);

  return Sigma2; }
//------------------PROGRAMA PRINCIPAL-------------------------
int main(void){
    LatticeGas Difusion;
    Crandom ran64(1);
    int N=400; //número de partícula
    double mu =Lx/2;
    double sigma = Lx/8;
    int t;
    int tmax=10000;

    Difusion.Borrese();
    Difusion.Inicie(N, mu, sigma, ran64);
    for (t=0; t<tmax;t++){
        std::cout << t << "\t " << Difusion.Varianza() << std::endl;
        Difusion.Colisione(ran64);
        Difusion.Adveccione();
    }
    // Difusion.GrafiqueRho();
    return 0;
}
