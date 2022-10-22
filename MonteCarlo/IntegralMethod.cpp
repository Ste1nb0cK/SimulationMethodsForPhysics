#include <cmath>
#include <iostream>
#include "Random64.h"

int main(void){
    Crandom ran64(1);
    double tau=3;
    for (int i=0; i<1e4; i++){
        std::cout << -tau*ran64.r()<< std::endl;
    }
    return 0;
    }
