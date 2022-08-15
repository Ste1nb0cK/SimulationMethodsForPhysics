# Simulation Methods For Physics Notes
Here I save the programs I am building for the course Métodos Computacionales en Física
(Computacional Methods in Physics). All of them based on the lectures given by professor 
Jose Daniel Muñoz at UNAL and consists primarily of slight modifications and improvements to the
code built in the lectures.

## 1. Bessel Functions
A  program that calculates [Bessel functions](https://en.wikipedia.org/wiki/Bessel_function)
by integrating the integral representation via [Simpson's rule](https://en.wikipedia.org/wiki/Simpson%27s_rule#Composite_Simpson's_rule) and also
a simple [bisection method](https://en.wikipedia.org/wiki/Bisection_method) script to find a zero between two given points. My main modification is parallelizing the calculation of the integral with [OpenMP](https://www.openmp.org/) and implementing Simpson's rule in a way that is general enough for use with any single variable function.
