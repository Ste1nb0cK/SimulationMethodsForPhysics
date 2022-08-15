#pragma once
#include <cmath>
#include <functional>
double IntegralPorSimpson(std::function<double(double)> f, int N, double a,
                          double b);
