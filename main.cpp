#include <SFML/Graphics.hpp>
#include "stdio.h"
#include <string.h>
#include <string>
#include "math.h"
#include <thread>
#include <chrono>
#include "Fluid.h"


int main(int args, char** argv){

    float WIDTH = 100;
    float HEIGHT = 100;

    float WINDOW_WIDTH = 1000;
    float WINDOW_HEIGHT = 1000;

    Fluid f(WIDTH, HEIGHT, 1);


    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            
            
            f.particles[coords2index(i, j, f.width)].vx = 0;
            f.particles[coords2index(i, j, f.width)].vy = 0;
            f.particles[coords2index(i, j, f.width)].p = 0;

            if(i >= 10 && i <= 20 && j >= 25 && j <= 35){
                f.particles[coords2index(i, j, f.width)].vx = 5;
            }

            if(j >= 10 && j <= 20 && i >= 25 && i <= 35){
                f.particles[coords2index(i, j, f.width)].vy = 5;
            }

        }
    }


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid Simulation");


    for(int i = 0; i < 100000; i++){
        f.physics(0.1);
        window.clear();
        drawParticles(window, f, 10);
        window.display();
    }


}