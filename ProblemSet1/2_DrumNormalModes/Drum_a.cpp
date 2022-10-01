/*This program solves the zero-th order Bessel equation by turning it into a
 *first order system of equations and then using the RK4 method on it.
 *The chosen substitution to define the system is x1=R, x2=\frac{dR}{dr}\}*/

//Initial conditions
double const x10 = 1; //function at r=0
double const x20 = 0; //derivative at r=0
double const t0 = 0.1; //initial time

//Simulation conditions
double const dt = 0.1; //step size
double const tf = 10; //final time
int const NMAX = 100000; //limit of iterations
#include <cmath>
#include <iostream>

//function that makes RK4 steps and updates the variables (time, x1 and x2).
//It also receives the extra parameter lambda.
void RKStep(double &t,double &x1, double &x2, double lambda);
//Functions that define the system. You can also pass and additional parameter
//lambda.
double f1(double t,double x1, double x2,  double lambda);
double f2(double t,double x1, double x2,  double lambda);


int main(void){
    double t, x1, x2;
    int N; //number of iterations
    double lambda = 1;
    //set initial conditions
    t = t0; x1=x10; x2= x20;
    std::cout << t << "\t" << x1 << "\t" << x2 <<  std::endl;
    for( N =0; (t<tf) &  (N<NMAX); N++){
        RKStep(x1, x2, t, lambda);
        std::cout << t << "\t" << x1  << "\t" << x2<< std::endl;
    }
    return 0;
}

double f1(double t,double x1, double x2,  double lambda){
    return x2;
}


double f2(double t,double x1, double x2,  double lambda){
    return -(x2/t)- lambda*lambda* x1;
}

void RKStep(double &x1, double &x2, double &t, double lambda){
    double dx11, dx21, dx31, dx41;
    double dx12, dx22, dx32, dx42;
    dx11 = f1(t,x1,x2, lambda)*dt;                                  dx12 = f2(t,x1,x2, lambda)*dt;
    dx21 = dt*f1(t+ 0.5*dt, x1 + 0.5*dx11, x2 + 0.5*dx12, lambda);  dx22 = dt*f2(t+ 0.5*dt, x1 + 0.5*dx11, x2 + 0.5*dx12, lambda);
    dx31 = dt*f1(t+ 0.5*dt, x1 + 0.5*dx21, x2 + 0.5*dx22, lambda);  dx32 = dt*f2(t+ 0.5*dt, x1 + 0.5*dx21, x2 + 0.5*dx22, lambda);
    dx41 = dt*f1(t+ 0.5*dt, x1 + dx31, x2 + dx32, lambda);          dx42 = dt*f2(t+ 0.5*dt, x1 + dx31, x2 + dx32, lambda);

    x1+=(dx11 + 2*dx21 + 2*dx31 + dx41)/6;
    x2+=(dx12 + 2*dx22 + 2*dx32 + dx42)/6;
    t+=dt;
}
