# Simulation Methods For Physics Notes
Here I save the programs I am building for the course Métodos Computacionales en Física
(Computacional Methods in Physics). All of them based on the lectures given by professor 
Jose Daniel Muñoz at UNAL and consists primarily of slight modifications and improvements to the
code built in the lectures.

## 1. Bessel Functions
A  program that calculates [Bessel functions](https://en.wikipedia.org/wiki/Bessel_function)
by integrating the integral representation via [Simpson's rule](https://en.wikipedia.org/wiki/Simpson%27s_rule#Composite_Simpson's_rule) and also
a simple [bisection method](https://en.wikipedia.org/wiki/Bisection_method) script to find a zero between two given points. My main modification is parallelizing the calculation of the integral with [OpenMP](https://www.openmp.org/) and implementing Simpson's rule in a way that is general enough for use with any single variable function.

## 2. Euler and Runge-Kutta methods
Implementations of [Euler](https://en.wikipedia.org/wiki/Euler_method#Derivation) and [RK4](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods#Implicit_Runge%E2%80%93Kutta_methods) (for a system of two coupled equations also) steps, I have rewritten the code a little bit so that it is easier to reuse. To actually obtain a numerical solution it is necessary to loop over the steps, they update the value of time and the depedent variable at each point. An example for the SHO is show in main.cpp.   

## 3. Introduction to Finite Elements and OOP
Implementation of the class Body to simulate the motion of a particle under a [Newtonian gravity](https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation) force. The class has methods for updating the state of the system, calculating the force and printing out positions. The initial conditions can be adjusted in Planet.cpp and the result plot is in OrbitPlot.pdf and the data of the positions and time is in data.dat. 

WARNING: you need python 3.0+, pandas and matplotlib to run the makefile as the script Plotter.py is in charge of creating the plot. 

## 4. Verlet Method
Very similar to the previous one, but know the method to updte the state is Verlet's algorithm and the library vector.h is used write the problem in a "vectorized" way.
