#include <cmath>
#include <iostream>
#include "Random64.h"

//---------------------Simulation Conditions-------------------------------------
const int Lx=256;
const int Ly=256;
const double p0=0.25; //probability to do nothing
const double p = 0.25; //probabilityy to rotate 90 degrees
const int Q=4; //number of possible directions to move
const int seed=1; //seed for the random generator
//---------------------initial Conditions----------------------------------------
const int N=2400; //number of particles
const double mu_x =Lx/2;
const double mu_y =Ly/2;
const double sigma_0 = 16;
const double sigma_x = sigma_0;
const double sigma_y = sigma_0;
const int tmax=350;
//-------Clase LatticeGas----------

class LatticeGas{
    private:
        int n[Lx][Ly][Q];//Matrix of Automatas
        int nnew[Lx][Ly][Q];//Use two copies for parallelism
//Directions Matrix. i=0 (right), i=1(up), i=2 (left), i=3 (down)
        int V[Q];
    public:
        LatticeGas(void);
        void Borrese(void); //reset all the cells to zero
        //initiate each cell
        void Inicie(int N,double mu_x, double mu_y,  double sigma_x,
                    double sigma_y, Crandom & ran64);
        //velocity updating for all the cells
        void Colisione(Crandom & ran64);
        //actual movement of the contents of each cell
        void Adveccione(void);
        //obtain the number of particles in a given cell
        double rho(int ix, int jy);
        double Varianza(void);
        //print the number of particles in each cell
        void GrafiqueRho(void);
};
LatticeGas::LatticeGas(void){
    //horizontales / verticales
    V[0]=1; V[1]=-1;
    V[2]=-1; V[3]=1;
}
void LatticeGas::Borrese(void){
    for(int ix=0; ix<Lx; ix++){
        for (int jy = 0; jy<Ly; jy++){
            for(int k=0; k<Q; k++){
                n[ix][jy][k]=nnew[ix][jy][k]=0;
            }
        }
    }
}
//this initiates the cell and only adds a particle to the cell if it is empty
//i.e. each cell begins with 1 or 0 particles.
//pass the generator by reference as we will use the same generator for
//for the whole simulation

void LatticeGas::Inicie(int N ,double mu_x, double mu_y,  double sigma_x,
                        double sigma_y, Crandom & ran64){
    int ix, jy ,k;
    while(N>0){
        //choose a cell at random
        ix=(int) ran64.gauss(mu_x, sigma_x);
        jy=(int) ran64.gauss(mu_y, sigma_y);
        //boundary corrections
        if(ix<0){ix=0;}
        if(jy<0){jy=0;}
        if(ix>Lx-1){ix=Lx-1;}
        if(jy>Ly-1){jy=Ly-1;}
        //choose direction randomly
        k = (int) Q*ran64.r();
        //add a particle to the cell, only if there is no particle. Decreese N
        if(n[ix][jy][k]==0){
            n[ix][jy][k]=1;
            N--;}
    }
}

void LatticeGas::GrafiqueRho(void){
    for (int ix=0; ix<Lx; ix++){
        for (int jy = 0; jy<Ly; jy++){
            std::cout << ix << ","<< jy <<"\t" << rho(ix, jy) << std::endl;
        }
    }
}

void LatticeGas::Colisione(Crandom & ran64){
    int ix, jy, k;
    for(ix=0; ix<Lx; ix++){
        for (jy=0; jy<Ly; jy++){
            //generate a random number between 0 and 1
            double alpha = ran64.r();
            //if p0<alpha<p+p0 rotate 90 degrees
            if((p0<alpha) & (alpha<p+p0)){
                for(k=0; k<Q; k++)
                    nnew[ix][jy][(k+1 + Q)%Q] = n[ix][jy][k];
            }
            // if p+p0<\alpha <  2p+p0 rotate 270° .
            else if((p0+p<alpha) &(alpha<p0+2*p)   ){
                for(k=0; k<Q; k++)
                    nnew[ix][jy][(k+3 + Q)%Q] = n[ix][jy][k];
            }
            //else rotate 180°
            else if((1-2*p-p0<alpha)) {
                for(k=0; k<Q; k++)
                    nnew[ix][jy][(k+2 + Q)%Q] = n[ix][jy][k];
            }
            //if 0<alpha <p0 do nothing
            else{
                for(k=0; k<Q; k++)
                    nnew[ix][jy][k] = n[ix][jy][k];
            }
        }
    }
}
void LatticeGas::Adveccione(void){
    for(int ix=0; ix<Lx;ix++){
        for(int jy=0; jy<Ly; jy++)
            for(int k=0; k<Q/2; k++){
                n[(ix+V[2*k]+Lx)%Lx][jy][2*k]=nnew[ix][jy][2*k];
                n[ix][(jy+ V[1+2*k])%Ly][1+2*k]=nnew[ix][jy][2*k+1];
            }
    }
}

double LatticeGas::rho(int ix, int jy){
    double sum =0;
    for(int k=0; k<Q; k++)
        sum += n[ix][jy][k];
    return sum;
}

//Variance in the position of the particles
double LatticeGas::Varianza(void){
    int ix, jy; double N,Xprom, Yprom,Sigma2x, Sigma2y, Sigma2;
    double rhox, rhoy;
    //Calculate N
    N=0;
    for(ix=0;ix<Lx;ix++)
        for(jy=0; jy<Ly;jy++)
            N+=rho(ix, jy);
    //Calculate Xprom and Yprom
    Xprom=0;
    Yprom=0;
    for(ix=0;ix<Lx;ix++)
        for(jy=0; jy<Ly; jy++){
          Xprom+=ix*rho(ix, jy);
          Yprom+=jy*rho(ix, jy);}
    Xprom/=N;
    Yprom/=N;
    //Calcular Sigma2
    Sigma2x = 0;
    Sigma2y = 0;
    Sigma2 = 0;
    // sigma2x
    for(ix = 0; ix<Lx; ix++){
        //Calculate marginal probability for the given ix
        for(jy = 0; jy<Ly; jy++)
            rhox += rho(ix, jy);
        Sigma2x += std::pow((Xprom - ix),2)*rhox;
        rhox = 0;
    }
    Sigma2x/=(N-1);
    for(jy = 0; jy<Ly; jy++){
        //Calculate marginal probability for the given ix
        for(ix = 0; ix<Lx; ix++)
            rhoy += rho(ix, jy);
        Sigma2y += std::pow((Yprom - jy),2)*rhoy;
        rhoy = 0;
    }
    Sigma2y/=(N-1);
    Sigma2 = Sigma2y + Sigma2x;
    return Sigma2; }
//------------------PROGRAMA PRINCIPAL-------------------------
int main(void){
    LatticeGas Difusion;
    Crandom ran64(1);
    int t;
    Difusion.Borrese();
    Difusion.Inicie(N, mu_x, mu_y, sigma_x, sigma_y, ran64);
    for (t=0; t<tmax;t++){
        std::cout << t << "\t " << Difusion.Varianza() << std::endl;
        Difusion.Colisione(ran64);
        Difusion.Adveccione();
    }
    // Difusion.GrafiqueRho();
    return 0;
}
