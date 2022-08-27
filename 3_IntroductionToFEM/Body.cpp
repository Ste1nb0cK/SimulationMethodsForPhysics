#include "Body.h"
#include "Constants.h"
#include <cmath>
void Body::initiate(double x0, double y0, double vx0, double vy0,
                    double m0, double R0){
    //Define the initial conditions of the simulation
    x = x0;
    y = x0;
    m = m0;
    vx = vx0;
    vy = vy0;
    R = R0;
}

void Body::calculateForce(void){
    //calculate the force at a given instant
    double r = std::sqrt( std::pow(x,2) + std::pow(y,2) );
    fx =-constants::GM*m *x/std::pow(r,3);
    fy =-constants::GM*m *y/std::pow(r,3);


}

void Body::move(double dt){
    //update the state of the system for the next state
    x +=vx*dt;
    y +=vy*dt;
    vy += fy/m * dt;
    vx += fx/m * dt;

}
