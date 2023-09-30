#include "examples.h"

void example1(Fluid& f){

    for(int i = 0; i < f.width; i++){
        for(int j = 0; j < f.height; j++){
        
            if(i >= 10 && i <= 20 && j >= 40 && j <= 44){
                f.particles[coords2index(i, j, f.width)].Fx = 100;
                f.particles[coords2index(i, j, f.width)].smoke = 0.5;
            }

            if(j >= 10 && j <= 20 && i >= 28 && i <= 32){
                f.particles[coords2index(i, j, f.width)].Fy = 200;
                f.particles[coords2index(i, j, f.width)].smoke = 0.5;
            }

        }
    }

}

void example2(Fluid& f){

    f.set_boundaries = set_bnd2;
    for(int i = 0; i < f.width; i++){
        for(int j = 0; j < f.height; j++){
        
            if(i >= 10 && i <= 20 && j >= 40 && j <= 44){
                f.particles[coords2index(i, j, f.width)].Fx = 100;
                f.particles[coords2index(i, j, f.width)].smoke = 0.5;
            }

            if(j >= 10 && j <= 20 && i >= 28 && i <= 32){
                f.particles[coords2index(i, j, f.width)].Fy = 200;
                f.particles[coords2index(i, j, f.width)].smoke = 0.5;
            }

        }
    }

}

void tunnel(Fluid& f){

    f.set_boundaries = tunnel_bnd;
    for(int j = 1; j < f.height - 1; j++){
        Particle& p = f.particles[coords2index(1, j, f.width)];
        
        if(j >= 40 && j <= 60){
            p.smoke = 0.5;
        }

        p.vx = 50;
    }

}