#include <SFML/Graphics.hpp>
#include "stdio.h"
#include <string.h>
#include <string>
#include "math.h"
#include <thread>
#include <chrono>
#include "Fluid.h"


int main(int args, char** argv){

    float WIDTH = 70;
    float HEIGHT = 70;

    float WINDOW_WIDTH = 700;
    float WINDOW_HEIGHT = 700;

    uint block_size = (uint) (WINDOW_WIDTH / WIDTH);

    float simulation_time = 20;
    float delta = 0.02;
    uint threads = 1;

    bool render = false;
    bool render_energy = false;
    bool render_velocities = false;
    for(int i = 0; i < args; i++){
        if(strcmp(argv[i], "-render") == 0){
            render = true;
        }

        if(strcmp(argv[i], "-energy") == 0){
            render_energy = true;
        }

        if(strcmp(argv[i], "-velocities") == 0){
            render_velocities = true;
        }

        if(strcmp(argv[i], "-time") == 0){
            simulation_time = atof(argv[i + 1]);
        }

        if(strcmp(argv[i], "-threads") == 0){
            threads = atoi(argv[i + 1]);
        }

    }

    Fluid f(WIDTH, HEIGHT, 1);
    f.gs_iters = 20;
    f.threads = threads;
    f.dx = 50.0 / HEIGHT;


    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            
            
            f.particles[coords2index(i, j, f.width)].vx = 0;
            f.particles[coords2index(i, j, f.width)].vy = 0;
            f.particles[coords2index(i, j, f.width)].p = 0;

            if(i >= 10 && i <= 20 && j >= 40 && j <= 44){
                f.particles[coords2index(i, j, f.width)].Fx = 100;
                f.particles[coords2index(i, j, f.width)].smoke = 1;
            }

            if(j >= 10 && j <= 20 && i >= 28 && i <= 32){
                f.particles[coords2index(i, j, f.width)].Fy = 200;
                f.particles[coords2index(i, j, f.width)].smoke = 1;
            }

        }
    }


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid Simulation");

    int frames = (int) (simulation_time / delta);
    for(int frame = 0; frame < frames; frame++){
        //time physics with chrono

        auto start = std::chrono::high_resolution_clock::now();
        f.physics(delta);
        auto end = std::chrono::high_resolution_clock::now();

        window.clear();
        drawParticles(window, f, block_size, render_energy, render_velocities);
        window.display();

        if(render){
            sf::Image screenshot = window.capture();
            
            screenshot.saveToFile("render/" + std::to_string(frame) + ".png");
            printf("Rendered frame %d at simulation time %fs\n", frame, frame*delta);
        }

        if(frame == 2){
            for(int i = 0; i < WIDTH; i++){
                for(int j = 0; j < HEIGHT; j++){
               
                    Particle& p = f.particles[coords2index(i, j, f.width)];
                    p.Fx = 0;
                    p.Fy = 0;

                }
            }
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