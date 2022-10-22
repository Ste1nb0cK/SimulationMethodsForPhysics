#include <cmath>
#include <iostream>

const int Lx=1024; //1024
const double p=0.5; //probabilidad de voltear los contenidos i.e. las velocidades

const int Q=2; //cantidad de direcciones en las que se puede mover
//-------Clase LatticeGas----------

class LatticeGas{
    private:
        double f[Lx][Q];//Matriz de autómatas
        double fnew[Lx][Q];//usamos dos copias para paralelismo
        int V[Q];//Matriz de Direcciones. i=0 (moverse a la derecha), i=1(moverse a la izquierda)
    public:
        LatticeGas(void);
        //Pasamos por Referencia porque se mantendrá siempre el mismo generador
        void Inicie(int N, double mu,  double sigma);
        void Colisione(void);
        void Adveccione(void);
        //obtenemos la cantidad de particulas
        double rho(int ix);
        double Varianza(void);
        void GrafiqueRho(void);
};
LatticeGas::LatticeGas(void){
    V[0]=1; V[1]=-1;
}

//esto inicia las celdas, pero ahora en vez de poner bolitas ponemos una
//distribución, por lo que ya no necesitamos el generador aleatorio
void LatticeGas::Inicie(int N ,double mu,  double sigma ){
    for(int ix=0; ix<Lx; ix++){
        double argument_gaussian = -0.5 * std::pow((ix-mu)/sigma, 2.0);
        double rho =N * 1/(sigma * std::sqrt(2*M_PI)) * std::exp(argument_gaussian);
        for (int i=0; i<Q; i++){
            f[ix][i] = rho/Q;
        }
    }
}
void LatticeGas::GrafiqueRho(void){
    for (int ix=0; ix<Lx; ix++)
        std::cout << ix << " " << rho(ix) << std::endl;
}
double LatticeGas::rho(int ix){
    double sum ;
    int i;
    for(sum =0, i =0; i<Q; i++){
        sum +=f[ix][i];
    }
    return sum;
}
//esta es la parte del coin flip i.e. actualización de velocidades
void LatticeGas::Colisione(void){
    int ix, i, j;
    for (ix=0;ix<Lx;ix++){//para cada celda
        for (i=0; i<Q; i++){ //para cada dirección
            j = (i+1)%Q;
            fnew[ix][i] = f[ix][i]+(1-p)*(f[ix][j]-f[ix][i]);
        }
}
}
void LatticeGas::Adveccione(void){
        for(int ix=0; ix<Lx;ix++)
            for(int i=0; i<Q; i++)
                f[(ix+V[i]+Lx)%Lx][i]=fnew[ix][i];
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
  Sigma2/=N;

  return Sigma2; }
//------------------PROGRAMA PRINCIPAL-------------------------
int main(void){
    LatticeGas Difusion;
    int N=400; //número de partícula
    double mu =Lx/2;
    double sigma = Lx/8;
    int t;
    int tmax=10000;

    Difusion.Inicie(N, mu, sigma);
    for (t=0; t<tmax;t++){
        std::cout << t << "\t " << Difusion.Varianza() << std::endl;
        Difusion.Colisione();
        Difusion.Adveccione();
    }
    // Difusion.GrafiqueRho();
    return 0;
}
