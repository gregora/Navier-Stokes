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

    float delta = 0.01;

    bool render = false;
    for(int i = 0; i < args; i++){
        if(strcmp(argv[i], "-render") == 0){
            render = true;
        }
    }

    Fluid f(WIDTH, HEIGHT, 1);


    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            
            
            f.particles[coords2index(i, j, f.width)].vx = 0;
            f.particles[coords2index(i, j, f.width)].vy = 0;
            f.particles[coords2index(i, j, f.width)].p = 0;

            if(i >= 10 && i <= 20 && j >= 28 && j <= 32){
                f.particles[coords2index(i, j, f.width)].vx = 5;
            }

            if(j >= 10 && j <= 20 && i >= 28 && i <= 32){
                f.particles[coords2index(i, j, f.width)].vy = 5;
            }

        }
    }


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid Simulation");


    for(int i = 0; i < 2000; i++){
        f.physics(delta);
        window.clear();
        drawParticles(window, f, 10, false);
        window.display();

        if(render){
            window.capture().saveToFile("render/" + std::to_string(i) + ".png");
            printf("Rendered frame %d at simulation time %fs\n", i, i*delta);
        }
    }

    if(render){
		printf("Rendering ...\n");
		system(std::string(("ffmpeg -y -framerate ") + std::to_string((int) (1 / delta)) + std::string(" -i render/%d.png render/output.mp4 > /dev/null")).c_str());
		printf("Deleting pngs ...\n");
		system("rm -r render/*.png");
		printf("Done.\n");
	}



}