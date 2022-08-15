#pragma once
#include <cmath>
#include <functional>

double CerosPorBiseccion(std::function<double(double)> f,
double a, double b);
