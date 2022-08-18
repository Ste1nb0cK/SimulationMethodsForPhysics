#pragma once
#include <functional>
void RK4Step(std::function<double (double, double)> f,double &t, double &x,
             double dt);
