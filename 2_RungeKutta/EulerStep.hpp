#pragma once
#include <functional>
void EulerStep(std::function<double (double, double)> ,double &t,
               double &x, double dt);
