//Class declaration
#pragma once

#include <cmath>
#include "vector.h"
#include "Constants.h"

class Body;

class Body{
    private:
                vector3D r, V, F;
                double m, R;
    public:
                void initiate(double x0, double y0, double z0, double vx0,
                              double vy0, double vz0,double m0, double R0);
                void calculateForce(void);
                void move(double dt);
                double Getx(void){return r.x();};
                double Gety(void){return r.y();};
                double Getz(void){return r.z();};
                double Getvx(void){return V.x();};
                double Getvy(void){return V.y();};
                double Getvz(void){return V.z();};
};
