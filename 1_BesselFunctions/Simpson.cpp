#include "Simpson.hpp"
#include <omp.h>
#include <iostream>
double IntegralPorSimpson(std::function<double(double)> f, int N, double a,
                          double b) {
    int n = N * 2;
    double h = (b - a) / n;
    double sum = 0;
    int i;
    int i0;
    int imax;
    int thid;
    int nth;
    //WARNING: it is assumed the number of threads is even and so n/nth.
#pragma omp parallel private(i, i0, imax) shared(a, b, h, n) reduction(+: sum)
    {
        nth = omp_get_num_threads();
        thid = omp_get_thread_num();
        i0 = n/nth * thid;
        imax = n/nth * (thid+1);
        //master takes care of the ends
        if( 0 == thid ){
            sum += f(a) + f(b);
            i0++;}

        for (i = i0; i < imax; i += 2) {
            sum += 2 * f(a + h * i);
        }
        for (i = i0+1; i < imax; i += 2) {
            sum += 4 * f(a + h * i);
        }
  }
  double f0 = f(a + 0 * h);
  double fn = f(a + h * n);
  sum += fn + f0;
  double integral = h / 3 * sum;
  return integral;
}
