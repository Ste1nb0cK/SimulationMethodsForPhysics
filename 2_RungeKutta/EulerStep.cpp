#include "EulerStep.hpp"
#include <functional>
void EulerStep(std::function<double (double, double)> f, double &t, double &x,
               double dt){
    double dx = f(t,x)*dt;
    x +=dx;
    t += dt;
}
