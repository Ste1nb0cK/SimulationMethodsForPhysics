//Class declaration
#pragma once
#include <cmath>
#include "Constants.h"
class Body;

class Body{
    private:
        double x,y, vx, vy, fx, fy, m, R;
    public:
        void initiate(double x0, double y0, double vx0, double vy0,double m0, double R0);
        void calculateForce(void);
        void move(double dt);
        double Getx(void){return x;};
        double Gety(void){return y;};
        double Getvx(void){return vx;};
        double Getvy(void){return vy;};
};
