#include "misc.h"

void set_bnd2(Particle* particles, uint width, uint height, uint identifier){

    //top and bottom
    for(uint i = 1; i < width - 1; i++){

        if(identifier == 1){
            particles[coords2index(i, 0, width)].vx = 0;
            particles[coords2index(i, height - 1, width)].vx = 0;
        }

        if(identifier == 2){
            particles[coords2index(i, 0, width)].vy = -particles[coords2index(i, 1, width)].vy;
            particles[coords2index(i, height - 1, width)].vy = -particles[coords2index(i, height - 2, width)].vy;
        }

        if(identifier == 3){
            particles[coords2index(i, 0, width)].div = particles[coords2index(i, 1, width)].div;
            particles[coords2index(i, height - 1, width)].div = particles[coords2index(i, height - 2, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(i, 0, width)].p = particles[coords2index(i, 1, width)].p;
            particles[coords2index(i, height - 1, width)].p = particles[coords2index(i, height - 2, width)].p;        
        }
    }

    //left and right
    for(uint j = 1; j < height - 1; j++){

        if(identifier == 1){
            particles[coords2index(0, j, width)].vx = -particles[coords2index(1, j, width)].vx;
            particles[coords2index(width - 1, j, width)].vx = -particles[coords2index(width - 2, j, width)].vx;
        }

        if(identifier == 2){
            particles[coords2index(0, j, width)].vy = 0;
            particles[coords2index(width - 1, j, width)].vy = 0;
        }

        if(identifier == 3){
            particles[coords2index(0, j, width)].div = particles[coords2index(1, j, width)].div;
            particles[coords2index(width - 1, j, width)].div = particles[coords2index(width - 2, j, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(0, j, width)].p = particles[coords2index(1, j, width)].p;
            particles[coords2index(width - 1, j, width)].p = particles[coords2index(width - 2, j, width)].p;
        }
    }

    //add another box
    uint box_x_start = 40;
    uint box_x_end = 60;

    uint box_y_start = 70;
    uint box_y_end = 80;

    for(uint i = box_x_start; i < box_x_end; i++){

        if(identifier == 1){
            particles[coords2index(i, box_y_start, width)].vx = 0;
            particles[coords2index(i, box_y_end - 1, width)].vx = 0;
        }

        if(identifier == 2){
            particles[coords2index(i, box_y_start, width)].vy = - particles[coords2index(i, box_y_start - 1, width)].vy;
            particles[coords2index(i, box_y_end - 1, width)].vy = - particles[coords2index(i, box_y_end, width)].vy;
        }

        if(identifier == 3){
            particles[coords2index(i, box_y_start, width)].div = particles[coords2index(i, box_y_start - 1, width)].div;
            particles[coords2index(i, box_y_end - 1, width)].div = particles[coords2index(i, box_y_end, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(i, box_y_start, width)].p = particles[coords2index(i, box_y_start - 1, width)].p;
            particles[coords2index(i, box_y_end - 1, width)].p = particles[coords2index(i, box_y_end, width)].p;
        }

    }

    for(uint j = box_y_start; j < box_y_end; j++){

        if(identifier == 1){
            particles[coords2index(box_x_start, j, width)].vx = - particles[coords2index(box_x_start - 1, j, width)].vx;
            particles[coords2index(box_x_end - 1, j, width)].vx = - particles[coords2index(box_x_end, j, width)].vx;
        }

        if(identifier == 2){
            particles[coords2index(box_x_start, j, width)].vy = 0;
            particles[coords2index(box_x_end - 1, j, width)].vy = 0;
        }

        if(identifier == 3){
            particles[coords2index(box_x_start, j, width)].div = particles[coords2index(box_x_start - 1, j, width)].div;
            particles[coords2index(box_x_end - 1, j, width)].div = particles[coords2index(box_x_end, j, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(box_x_start, j, width)].p = particles[coords2index(box_x_start - 1, j, width)].p;
            particles[coords2index(box_x_end - 1, j, width)].p = particles[coords2index(box_x_end, j, width)].p;
        }

    }

    for(uint i = box_x_start + 1; i < box_x_end - 1; i++){
        for(uint j = box_y_start + 1; j < box_y_end - 1; j++){
            
            if(identifier == 1){
                particles[coords2index(i, j, width)].vx = 0.0;
            }

            if(identifier == 2){
                particles[coords2index(i, j, width)].vy = 0.0;
            }

            if(identifier == 3){
                particles[coords2index(i, j, width)].div = 0.0;
            }

            if(identifier == 4){
                particles[coords2index(i, j, width)].p = 0.0;
            }
            

            if(identifier == 5){
                particles[coords2index(i, j, width)].smoke = 0.0;
            }
        }
    }




}


void tunnel_bnd(Particle* particles, uint width, uint height, uint identifier){


    //top and bottom
    for(uint i = 1; i < width - 1; i++){

        if(identifier == 1){
            particles[coords2index(i, 0, width)].vx = particles[coords2index(i, 1, width)].vx;
            particles[coords2index(i, height - 1, width)].vx = particles[coords2index(i, height - 2, width)].vx;
        }

        if(identifier == 2){
            particles[coords2index(i, 0, width)].vy = 0;
            particles[coords2index(i, height - 1, width)].vy = 0;
        }

        if(identifier == 3){
            particles[coords2index(i, 0, width)].div = particles[coords2index(i, 1, width)].div;
            particles[coords2index(i, height - 1, width)].div = particles[coords2index(i, height - 2, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(i, 0, width)].p = particles[coords2index(i, 1, width)].p;
            particles[coords2index(i, height - 1, width)].p = particles[coords2index(i, height - 2, width)].p;        
        }

        if(identifier == 5){
            particles[coords2index(i, 0, width)].smoke = particles[coords2index(i, 1, width)].smoke;
            particles[coords2index(i, height - 1, width)].smoke = particles[coords2index(i, height - 2, width)].smoke;
        }
    }

    //left and right
    for(uint j = 1; j < height - 1; j++){

        if(identifier == 1){
            particles[coords2index(0, j, width)].vx = particles[coords2index(1, j, width)].vx;
            particles[coords2index(width - 1, j, width)].vx = particles[coords2index(width - 2, j, width)].vx;
        }

        if(identifier == 2){
            particles[coords2index(0, j, width)].vy = particles[coords2index(1, j, width)].vy;
            particles[coords2index(width - 1, j, width)].vy = particles[coords2index(width - 2, j, width)].vy;
        }

        if(identifier == 3){
            particles[coords2index(0, j, width)].div = particles[coords2index(1, j, width)].div;
            particles[coords2index(width - 1, j, width)].div = particles[coords2index(width - 2, j, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(0, j, width)].p = particles[coords2index(1, j, width)].p;
            particles[coords2index(width - 1, j, width)].p = particles[coords2index(width - 2, j, width)].p;
        }

        if(identifier == 5){
            particles[coords2index(0, j, width)].smoke = particles[coords2index(1, j, width)].smoke;
            particles[coords2index(width - 1, j, width)].smoke = particles[coords2index(width - 2, j, width)].smoke;
        }
    }

    //add another box
    uint box_x_start = 30;
    uint box_x_end = 40;

    uint box_y_start = 45;
    uint box_y_end = 55;

    for(uint i = box_x_start; i < box_x_end; i++){

        if(identifier == 1){
            particles[coords2index(i, box_y_start, width)].vx = 0;
            particles[coords2index(i, box_y_end - 1, width)].vx = 0;
        }

        if(identifier == 2){
            particles[coords2index(i, box_y_start, width)].vy = - particles[coords2index(i, box_y_start - 1, width)].vy;
            particles[coords2index(i, box_y_end - 1, width)].vy = - particles[coords2index(i, box_y_end, width)].vy;
        }

        if(identifier == 3){
            particles[coords2index(i, box_y_start, width)].div = particles[coords2index(i, box_y_start - 1, width)].div;
            particles[coords2index(i, box_y_end - 1, width)].div = particles[coords2index(i, box_y_end, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(i, box_y_start, width)].p = particles[coords2index(i, box_y_start - 1, width)].p;
            particles[coords2index(i, box_y_end - 1, width)].p = particles[coords2index(i, box_y_end, width)].p;
        }

    }

    for(uint j = box_y_start; j < box_y_end; j++){

        if(identifier == 1){
            particles[coords2index(box_x_start, j, width)].vx = - particles[coords2index(box_x_start - 1, j, width)].vx;
            particles[coords2index(box_x_end - 1, j, width)].vx = - particles[coords2index(box_x_end, j, width)].vx;
        }

        if(identifier == 2){
            particles[coords2index(box_x_start, j, width)].vy = 0;
            particles[coords2index(box_x_end - 1, j, width)].vy = 0;
        }

        if(identifier == 3){
            particles[coords2index(box_x_start, j, width)].div = particles[coords2index(box_x_start - 1, j, width)].div;
            particles[coords2index(box_x_end - 1, j, width)].div = particles[coords2index(box_x_end, j, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(box_x_start, j, width)].p = particles[coords2index(box_x_start - 1, j, width)].p;
            particles[coords2index(box_x_end - 1, j, width)].p = particles[coords2index(box_x_end, j, width)].p;
        }

    }

    for(uint i = box_x_start + 1; i < box_x_end - 1; i++){
        for(uint j = box_y_start + 1; j < box_y_end - 1; j++){
            
            if(identifier == 1){
                particles[coords2index(i, j, width)].vx = 0.0;
            }

            if(identifier == 2){
                particles[coords2index(i, j, width)].vy = 0.0;
            }

            if(identifier == 3){
                particles[coords2index(i, j, width)].div = 0.0;
            }

            if(identifier == 4){
                particles[coords2index(i, j, width)].p = 0.0;
            }
            

            if(identifier == 5){
                particles[coords2index(i, j, width)].smoke = 0.0;
            }
        }
    }


    particles[coords2index(0, 0, width)].vx = particles[coords2index(0, 1, width)].vx;
    particles[coords2index(0, 0, width)].vy = particles[coords2index(1, 0, width)].vy;

    particles[coords2index(width - 1, 0, width)].vx = particles[coords2index(width - 1, 1, width)].vx;
    particles[coords2index(width - 1, 0, width)].vy = particles[coords2index(width - 2, 0, width)].vy;

    particles[coords2index(0, height - 1, width)].vx = particles[coords2index(0, height - 2, width)].vx;
    particles[coords2index(0, height - 1, width)].vy = particles[coords2index(1, height - 1, width)].vy;

    particles[coords2index(width - 1, height - 1, width)].vx = particles[coords2index(width - 1, height - 2, width)].vx;
    particles[coords2index(width - 1, height - 1, width)].vy = particles[coords2index(width - 2, height - 1, width)].vy;

}
