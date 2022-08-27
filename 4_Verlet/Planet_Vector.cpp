#include <iostream>
#include "Body.h"
int main(){
  Body Planeta;
  double r0=10,m0=1;
  double omega,V0,T;
  double t,dt=0.01;

  omega=sqrt(constants::GM/(r0*r0*r0)); V0=omega*r0; T=2*M_PI/omega;

  //------------(x0,y0,Vx0,Vy0,m0,R0)
  Planeta.initiate(r0, 0,0,  0, V0/2, 0,m0,0.5);
  for(t=0;t<1.1*T;t+=dt){
    std::cout<<Planeta.Getx()<<"\t "<<Planeta.Gety()<<std::endl;
    Planeta.calculateForce();
    Planeta.move(dt);
  }

  return 0;
}
