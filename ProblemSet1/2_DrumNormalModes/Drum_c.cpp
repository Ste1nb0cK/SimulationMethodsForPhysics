/*This program focus on finding by bisection the zeros of f_lamba, the function
that was implemented in part b. From ploting f_lambda we know that the zeros
are located in the following intervals:
       a      b
0   2.44   2.45
1   5.72   5.73
2   9.09   9.10
3  12.51  12.52
*/

//Initial conditions
double const x10 = 1; //function at r=0
double const x20 = 0; //derivative at r=0
double const t0 = 0.1; //initial time

//Simulation conditions
double const dt = 0.0001; //step size
double const tf = 1; //final time
int const NMAX = 100000;//limit of iterations
                        //
#include <cmath>
#include <iostream>
#include <functional>

//function that makes a bisection method on a given interva (a,b) and a function
//f of a single double variable
double Bisection(double a, double b, std::function<double(double)> f);

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
    std::cout.precision(16); std::cout.setf(std::ios::scientific);
    std::cout << Bisection(2.44,   2.45, f_lambda) << std::endl;
    std::cout << Bisection(5.72,   5.73, f_lambda) << std::endl;
    std::cout << Bisection(9.09,   9.10, f_lambda) << std::endl;
    std::cout << Bisection(12.51,   12.52, f_lambda) << std::endl;
    return 0;
}

double Bisection(double a, double b, std::function<double(double)> f){
  const double ErrMax = 1e-7; //tolerance
  double m;
  double fm;
  double fa = f(a);
  while (b - a > ErrMax) {
    m = (b + a) / 2;
    if (fa * fm > 0) {
      fm = f(m);
      a = m;
      fa = fm;
    } else
      b = m;
  }
  return m;
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
