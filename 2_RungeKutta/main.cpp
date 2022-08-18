#include <iostream>
#include <cmath>
#include "RK4CoupledStep.hpp"
double f(double t, double x);
double f1(double t, double x1, double x2);
double f2(double t, double x1, double x2);
int main(void){
    double t, x1, x2;
    double dt = 0.01;
    for(t=0, x1=1, x2=2 ;t<4+dt/2;){
        std::cout<< t <<" " << x1 <<" " <<std::exp(t) << std::endl;
        RK4CoupledStep(f1, f2,t, x1, x2, dt);
    }
    return 0;
}



double f(double t, double x){
    return x;
}


double f1(double t, double x1, double x2){
    const double omega = 1;
    return -omega *omega *x2;
}

double f2(double t, double x1, double x2){
    return x1;
}
