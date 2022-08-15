#include "Bisection.hpp"


double CerosPorBiseccion(std::function<double(double)> f, double a, double b) {
  const double ErrMax = 1e-7;
  double m;
  double fm;
  double fa = f(a);
  while (b - a > ErrMax) {
    m = (b + a) / 2;
    if (fa * fm > 0) {
      fm = f(m);
      a = m;
      fa = fm;
    } else
      b = m;
  }
  return m;
}
