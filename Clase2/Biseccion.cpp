#include <cmath>
#include <iostream>
#include <numbers>
double BesselIntegrand(double alpha, double x, double t);
double IntegralPorSimpson(double (*f)(double, double, double), double alpha,
                          double x, int N, double a, double b);
double CerosPorBiseccion( double (*f)(double, double, double), double a,
                          double b);
double BesselFunctions (double alpha, double x);
int main(void){
    const double A = 0;
    const double B = M_PI_2;
    double x = 0;
    for (int k=0; k<100; k++ ){
        x += 1/10;
        std::cout <<x << "\t" <<BesselFunctions(x, 10) << std::endl;}
    return 0;
}

double BesselIntegrand(double alpha, double x, double t){
    return std::cos(alpha*t - x*std::sin(t));
}

double BesselFunctions (double alpha, double x){
    double J = IntegralPorSimpson(*BesselIntegrand, alpha , x, 50 ,0, M_PI)/M_PI;
    return J;
}

double IntegralPorSimpson(double (*f)(double, double, double), double alpha,
                          double x,int N,double a, double b){
    int n = N*2;
    double h = (b-a)/n;
    double sum = 0;
    double f0 = f(alpha,x, a+0*h);
    sum += f0;
    for (int i=1; i<=n-1; i += 2){
        sum += 4*f(alpha, x, a + h*i);
    }
    for (int i=2; i<=n-1; i += 2){
        sum += 2*f(alpha, x, a + h*i);
    }
    double fn = f(alpha, x, a + h*n);
    sum += fn;
    double integral = h/3 * sum;
    return integral;
}



double CerosPorBiseccion( double (*f)(double ),
                          double a, double b){
    const double ErrMax=1e-7;
    double m;
    double fa = f(a);
    double fm;
    while(b-a>ErrMax){
        m = (b+a)/2;
        if (fa*fm>0) { //correr a hasta m
        fm = f(m);
            a = m;
             fa = fm;}
        else b=m; //correr b hasta m
    }
    return m;
}
