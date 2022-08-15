#include <cmath>
#include <functional>
#include <iostream>

double CerosPorBiseccion(std::function<double(double)> f, double a, double b);
double IntegralPorSimpson(std::function<double(double)> f, int N, double a,
                          double b);
double BesselIntegrand(double alpha, double x, double t);
double BesselFunctions(double alpha, double x);

int main(void) {
  double alpha = 0;
  double x;
  int N = 1000;
  double xo = 0;
  double xf = 10;
  double dx = (xf - xo) / N;
  for (int k = 0; k <= 1000; k++) {
    x += dx;
    std::cout << x << "\t" << BesselFunctions(alpha, x) << std::endl;
  }
  return 0;
}

double BesselFunctions(double alpha, double x) {
  // define a lambda to use a restricted form of the integrand
  auto f = [&alpha, &x](double t) { return BesselIntegrand(alpha, x, t); };
  const int N = 50;
  const double A = 0;
  const double B = M_PI;
  double bessel_x = IntegralPorSimpson(f, N, A, B);
  return bessel_x;
}

double BesselIntegrand(double alpha, double x, double t) {
  return 1 / M_PI * std::cos(alpha * t - x * std::sin(t));
}

double IntegralPorSimpson(std::function<double(double)> f, int N, double a,
                          double b) {
  int n = N * 2;
  double h = (b - a) / n;
  double sum = 0;
  double f0 = f(a + 0 * h);
  sum += f0;
  for (int i = 1; i <= n - 1; i += 2) {
    sum += 4 * f(a + h * i);
  }
  for (int i = 2; i <= n - 1; i += 2) {
    sum += 2 * f(a + h * i);
  }
  double fn = f(a + h * n);
  sum += fn;
  double integral = h / 3 * sum;
  return integral;
}

double CerosPorBiseccion(std::function<double(double)> f, double a, double b) {
  const double ErrMax = 1e-7;
  double m;
  double fa = f(a);
  double fm;
  while (b - a > ErrMax) {
    m = (b + a) / 2;
    if (fa * fm > 0) { // correr a hasta m
      fm = f(m);
      a = m;
      fa = fm;
    } else
      b = m; // correr b hasta m
  }
  return m;
}
