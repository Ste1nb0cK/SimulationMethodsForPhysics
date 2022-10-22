//x1=s, x2=i, r=1-s-i
#include <iostream>
#include <cmath>
//constantes
double const BETA=0.35;
double const GAMMA=0.08;

//condiciones iniciales
double const s_0 = 0.999;
double const i_0 = 0.001;

//Pasos y tamaño
double const t0=0;
double const tf=70;
double const dt=0.01;
int const NMAX = (t0-tf)/dt;

//function that makes the RK4 steps. It gets as input the functions of the
//at the point the point at which to evaluate it and the time step. The function
//takes care of updating both time and the x's
void RK4Step(double &t0 ,double &x10,double &x20,  double dt);
double f1(double t, double x1, double x2);
double f2(double t, double x1, double x2);
int main(void){

    double t,s,i,r;
    //initiate initial conditions
    t=t0;
    s=s_0;
    i=i_0;
    r=1-s-i;
    while(t<tf){
        std::cout << t << "\t" << s << "\t" << i << "\t" << 1-i-s << std::endl;
        RK4Step(t, s, i, dt);
    }

    return 0;
}


void RK4Step(double &t0, double &x10, double &x20, double dt){

  double dx11, dx21, dx31, dx41;
  double dx12, dx22, dx32, dx42;


  dx11 = f1(t0, x10,x20)*dt;                                  dx12 = f2(t0,x10,x20)*dt;

  dx21 = dt*f1(t0+ 0.5*dt, x10 + 0.5*dx11, x20 + 0.5*dx12 );  dx22 = dt*f2(t0+ 0.5*dt, x10 + 0.5*dx11, x20 + 0.5*dx12);

  dx31 = dt*f1(t0+ 0.5*dt, x10 + 0.5*dx21, x20 + 0.5*dx22);  dx32 = dt*f2(t0+ 0.5*dt, x10 + 0.5*dx21, x20 + 0.5*dx22);

  dx41 = dt*f1(t0+ 0.5*dt, x10 + dx31, x20 + dx32 );          dx42 = dt*f2(t0+ 0.5*dt, x10 + dx31, x20 + dx32 );


  x10+=(dx11 + 2*dx21 + 2*dx31 + dx41)/6;
  x20+=(dx12 + 2*dx22 + 2*dx32 + dx42)/6;
  t0+=dt;
}

double f1(double t, double x1, double x2){
   return -BETA*x1*x2;
}

double f2(double t, double x1, double x2){
    return BETA*x1*x2 - GAMMA*x2;
}
