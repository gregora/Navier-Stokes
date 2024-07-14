#include "misc.h"

void ExampleFluid1::set_boundaries(Particle* particles, uint width, uint height, uint identifier){

    for(int i = 28; i <= 32; i++){
        for(int j = 10; j <= 20; j++){     
            particles[coords2index(i, j, width)].Fy = 200;
            particles[coords2index(i, j, width)].smoke = 0.5;
        }
    }

    for(int i = 10; i <= 20; i++){
        for(int j = 40; j <= 44; j++){
            particles[coords2index(i, j, width)].Fx = 100;
            particles[coords2index(i, j, width)].smoke = 0.5;
        }
    }

}

void ExampleFluid2::set_boundaries(Particle* particles, uint width, uint height, uint identifier){  

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
        
            if(i >= 10 && i <= 20 && j >= 40 && j <= 44){
                particles[coords2index(i, j, width)].Fx = 100;
                particles[coords2index(i, j, width)].smoke = 0.5;
            }

            if(j >= 10 && j <= 20 && i >= 28 && i <= 32){
                particles[coords2index(i, j, width)].Fy = 200;
                particles[coords2index(i, j, width)].smoke = 0.5;
            }

        }
    }

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


void TunnelFluid::set_boundaries(Particle* particles, uint width, uint height, uint identifier){

    for(int j = 1; j < height - 1; j++){
        Particle& p = particles[coords2index(1, j, width)];
        
        if(j >= 40 && j <= 60){
            p.smoke = 0.5;
        }

        p.vx = 50;
    }

    //top and bottom
    for(uint i = 1; i < width - 1; i++){

        if(identifier == 1){
            particles[coords2index(i, 0, width)].vx = 50;
            particles[coords2index(i, height - 1, width)].vx = 50;
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
    uint box_x_start = 20;
    uint box_x_end = 30;

    uint box_y_start = 48;
    uint box_y_end = 52;

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

        if(identifier == 5){
            particles[coords2index(i, box_y_start, width)].smoke = particles[coords2index(i, box_y_start - 1, width)].smoke;
            particles[coords2index(i, box_y_end - 1, width)].smoke = particles[coords2index(i, box_y_end, width)].smoke;
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

        if(identifier == 5){
            particles[coords2index(box_x_start, j, width)].smoke = particles[coords2index(box_x_start - 1, j, width)].smoke;
            particles[coords2index(box_x_end - 1, j, width)].smoke = particles[coords2index(box_x_end, j, width)].smoke;
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


    if (identifier == 3 || identifier == 4)
    {
        particles[coords2index(0, 0, width)].vx = 50;
        particles[coords2index(0, 0, width)].vy = 0;

        particles[coords2index(width - 1, 0, width)].vx = 50;
        particles[coords2index(width - 1, 0, width)].vy = 0;

        particles[coords2index(0, height - 1, width)].vx = 50;
        particles[coords2index(0, height - 1, width)].vy = 0;

        particles[coords2index(width - 1, height - 1, width)].vx = 50;
        particles[coords2index(width - 1, height - 1, width)].vy = 0;
    }
    
}


void postProcessingTunnel(sf::RenderWindow& window, uint block_size){

    uint box_x_start = 20;
    uint box_x_end = 30;

    uint box_y_start = 48;
    uint box_y_end = 52;

    uint width = (box_x_end - box_x_start)*block_size;
    uint height = (box_y_end - box_y_start)*block_size;

    sf::RectangleShape box(sf::Vector2f(width, height));

    box.setPosition(box_x_start*block_size, box_y_start*block_size);

    window.draw(box);

}