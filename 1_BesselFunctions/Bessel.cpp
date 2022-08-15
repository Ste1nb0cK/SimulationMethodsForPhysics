#include "Bessel.hpp"
#include "Simpson.hpp"

double BesselFunctions(double alpha, double x) {
  // define a lambda to use a restricted form of the integrand
  auto f = [&alpha, &x](double t) { return BesselIntegrand(alpha, x, t); };
  const int N = 100;
  const double A = 0;
  const double B = M_PI;
  double bessel_x = IntegralPorSimpson(f, N, A, B);
  return bessel_x;
}

double BesselIntegrand(double alpha, double x, double t) {
  return 1 / M_PI * std::cos(alpha * t - x * std::sin(t));
}
