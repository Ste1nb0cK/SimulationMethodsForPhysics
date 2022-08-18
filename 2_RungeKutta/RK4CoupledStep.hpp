#pragma once
#include <functional>
void RK4CoupledStep( std::function <double (double, double, double)> f1,
                     std::function <double (double, double, double)> f2 ,double &t, double &x,
                     double &y, double dt);
