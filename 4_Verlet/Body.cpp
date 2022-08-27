#include "Body.h"
void Body::initiate(double x0, double y0, double z0 , double vx0, double vy0,
                    double vz0, double m0, double R0){
    //Define the initial conditions of the simulation
    r.load(x0, y0, z0);
    r.load(vx0, vy0, vz0);
    m = m0;
    R = R0;
}

void Body::calculateForce(void){
    //calculate the force at a given instant
    double aux=constants::GM*m *1/(r.norm2()*r.norm());
    F = (-aux)*r;


}

void Body::move(double dt){
    //update the state of the system for the next state
    r += V*dt;
    V += F*(dt/m);

}
