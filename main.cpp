#include <SFML/Graphics.hpp>
#include "stdio.h"
#include <string.h>
#include <string>
#include "math.h"
#include <thread>
#include <chrono>
#include "misc.h"
#include "examples.h"
#include "Fluid.h"


int main(int args, char** argv){

    float WIDTH = 120;
    float HEIGHT = 100;

    float WINDOW_WIDTH = 1200;
    float WINDOW_HEIGHT = 1000;

    uint block_size = (uint) (WINDOW_WIDTH / WIDTH);

    float simulation_time = 20;
    float delta = 0.04;
    uint threads = 1;
    uint example = 1;

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

        if(strcmp(argv[i], "-example") == 0){
            example = atoi(argv[i + 1]);
        }

    }

    Fluid f(WIDTH, HEIGHT, 1);
    f.gs_iters = 20;
    f.threads = threads;
    f.dx = 50.0 / HEIGHT;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid Simulation");

    int frames = (int) (simulation_time / delta);
    for(int frame = 0; frame < frames; frame++){

        if(example == 1){
            example1(f);
        }else if (example == 2){
            example2(f);
        }else if (example == 3){
            tunnel(f);
        }
        

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
    }

    if(render){
		printf("Rendering ...\n");
		system(std::string(("ffmpeg -y -framerate ") + std::to_string((int) (1 / delta)) + std::string(" -i render/%d.png render/output.mp4 > /dev/null")).c_str());
		printf("Deleting pngs ...\n");
		system("rm -r render/*.png");
		printf("Done.\n");
	}

}