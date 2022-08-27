#include <cmath>
#include <iostream>
#include "Body.h"
#include "Constants.h"
//Movement of a planet under a central force.
int main(void){
    std::cout.setf(std::ios::scientific); std::cout.precision(16);
    double t, dt=0.0001;
    Body Planeta;
    double r=10;
    double omega = std::sqrt( constants::GM/ std::pow(r,3) );
    double v0 = omega * r;
    Planeta.initiate(r, 0, 0, v0/2, 1, 0.15);
    //run until a full period is completed
    for(t=0; t<2 * M_PI/omega; t+=dt){
        std::cout << Planeta.Getx() << "\t " << Planeta.Gety() << std::endl;
        Planeta.calculateForce();
        Planeta.move(dt);
    }
    return 0;
}
