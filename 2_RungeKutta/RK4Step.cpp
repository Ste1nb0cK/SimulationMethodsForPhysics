#include "RK4Step.hpp"

void RK4Step(std::function<double (double, double)> f, double &t, double &x,
             double dt){
    double dx1, dx2, dx3, dx4;
    dx1 = dt*f(t,x);
    dx2 = dt *  f(t + dt/2, x + dx1/2);
    dx3 = dt * f(t+dt/2, x + dx2/2);
    dx4 = dt * f(t + dt, x + dx3);
    double dx = (dx1 + 2*(dx2 +dx3) + dx4)/6;
    x +=dx;
    t += dt;
}
