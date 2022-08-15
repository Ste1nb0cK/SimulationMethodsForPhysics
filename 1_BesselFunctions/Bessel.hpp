#pragma once
#include <cmath>
#include <functional>
#include "Simpson.hpp"
double IntegralPorSimpson(std::function<double(double)> f, int N, double a,
                          double b);
double BesselIntegrand(double alpha, double x, double t);
double BesselFunctions(double alpha, double x);
