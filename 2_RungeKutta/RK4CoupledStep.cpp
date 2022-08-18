#include "RK4CoupledStep.hpp"

void RK4CoupledStep( std::function <double (double, double, double)> f1,
                     std::function <double (double, double, double)> f2 ,double &t, double &x1,
                     double &x2, double dt){
    double dx11, dx21, dx31, dx41; double dx12, dx22, dx32, dx42;

    dx11 = dt*f1(t,x1, x2); dx12 = dt*f2(t,x1, x2);

    dx21 = dt *  f1(t + dt/2, x1 + dx11/2, x2 + dx12/2);
    dx22 = dt *  f2(t + dt/2, x1 + dx11/2, x2 + dx12/2);

    dx31 = dt * f1(t+dt/2, x1 + dx21/2, x2 + dx22/2);
    dx32 = dt * f2(t+dt/2, x1 + dx21/2, x2 + dx22/2);

    dx41 = dt * f1(t + dt, x1 + dx31, x2 + dx32);
    dx42 = dt * f2(t + dt, x1 + dx31, x2 + dx32);

    double dx1 = (dx11 + 2*(dx21 +dx31) + dx41)/6;
    double dx2 = (dx12 + 2*(dx22 +dx32) + dx42)/6;

    x1 +=dx1;
    x2 +=dx2;
    t += dt;


}
