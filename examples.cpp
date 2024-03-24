#include "examples.h"


Fluid* example1(uint width, uint height, float dx){

    ExampleFluid1* fluid = new ExampleFluid1(width, height, 1);
    return fluid;

}

Fluid* example2(uint width, uint height, float dx){

    ExampleFluid2* fluid = new ExampleFluid2(width, height, 1);
    return fluid;

}

Fluid* tunnel(uint width, uint height, float dx){

    TunnelFluid* fluid = new TunnelFluid(width, height, 1);
    return fluid;

}

