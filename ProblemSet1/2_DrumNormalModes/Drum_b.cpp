//This program solves the zero-th order Bessel equation as the previous one,
//but now multiple simulations changing lambda and terminating at r=1 are
//run to obtain a function f(\lambda) = R(r=1; \lambda=1). The zeros of this
//function correspond with the lambdas that satistfy the boundary condition.

//Initial conditions
double const x10 = 1; //function at r=0
double const x20 = 0; //derivative at r=0
double const t0 = 0.1; //initial time

//Simulation conditions
double const dt = 0.01; //step size
double const tf = 1; //final time
int const NMAX = 100000; //limit of iterations
#include <cmath>
#include <iostream>

//functiont that obtains the f_lambda by running the simulation and evaluating
// R at r=1 i.e. at the boundary
double f_lambda(double lambda);
//function that runs the simulation with a given lambda i.e iterates RKStep
//with the given lambda.
void RunSimulation(double &t, double &x1, double &x2, double lambda);
//function that makes RK4 steps and updates the variables (time, x1 and x2).
//It also receives the extra parameter lambda.
void RKStep(double &t,double &x1, double &x2, double lambda);
//Functions that define the system. You can also pass and additional parameter
//lambda.
double f1(double t,double x1, double x2,  double lambda);
double f2(double t,double x1, double x2,  double lambda);


int main(void){
    double lambda = 0;
    double lambda_0 = 0.01;
    double dlambda = 0.01;
    double lambda_f = 15;
    int Nsteps = (lambda_f - lambda_0)/dlambda;
    for(int k=0; k<Nsteps; k++){
        std::cout << lambda << "\t"<<f_lambda(lambda) << std::endl;
        lambda += dlambda;
    }
    return 0;
}

double f_lambda(double lambda){
    double t,x1, x2;
    RunSimulation(t, x1, x2, lambda);
    return x1;
}

void RunSimulation(double &t, double &x1, double &x2, double lambda){
    t = t0; x1=x10; x2= x20; //set initial conditions
    int N; //number of iterations
    for(N =0; (t<tf) &  (N<NMAX); N++){
        RKStep(x1, x2, t, lambda);
     }

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
