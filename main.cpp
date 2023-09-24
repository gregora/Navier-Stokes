#include <SFML/Graphics.hpp>
#include "stdio.h"
#include <string.h>
#include <string>
#include "math.h"
#include <thread>
#include <chrono>

struct Particle {

    float vx = 0;
    float vy = 0;
    
    float p = 0;

};


int coords2index(int x, int y, int width){

    return y * width + x;

}

class Fluid {

    public:
        uint width;
        uint height;
        float dx;

        Particle* particles;

        Fluid(uint width, uint height, float dx){

            this->width = width;
            this->height = height;

            this->dx = dx;

            particles = new Particle[width * height];

        }

        void physics(float delta){

            Particle* newParticles = new Particle[width * height];

            float viscosity = 0.1;
            float max_change = 0;

            for(uint i = 1; i < width - 1; i++){
                for(uint j = 1; j < height - 1; j++){
                    Particle& p = particles[coords2index(i, j, width)];


                    float vx = p.vx;
                    float vy = p.vy;
                    
                    float vxx = (particles[coords2index(i + 1, j, width)].vx - particles[coords2index(i - 1, j, width)].vx) / (2 * dx);
                    float vxy = (particles[coords2index(i, j + 1, width)].vx - particles[coords2index(i, j - 1, width)].vx) / (2 * dx);

                    float vyy = (particles[coords2index(i, j + 1, width)].vy - particles[coords2index(i, j - 1, width)].vy) / (2 * dx);
                    float vyx = (particles[coords2index(i + 1, j, width)].vy - particles[coords2index(i - 1, j, width)].vy) / (2 * dx);

                    float vxxx = (particles[coords2index(i + 1, j, width)].vx - 2 * particles[coords2index(i + 1, j, width)].vx + 2 * particles[coords2index(i, j, width)].vx + particles[coords2index(i - 1, j, width)].vx) / (dx * dx);
                    float vxyy = (particles[coords2index(i, j + 1, width)].vx - 2 * particles[coords2index(i, j, width)].vx + 2 * particles[coords2index(i, j - 1, width)].vx + particles[coords2index(i, j - 1, width)].vx) / (dx * dx);

                    float vyxx = (particles[coords2index(i + 1, j, width)].vy - 2 * particles[coords2index(i, j, width)].vy + 2 * particles[coords2index(i - 1, j, width)].vy + particles[coords2index(i - 1, j, width)].vy) / (dx * dx);
                    float vyyy = (particles[coords2index(i, j + 1, width)].vy - 2 * particles[coords2index(i, j, width)].vy + 2 * particles[coords2index(i, j - 1, width)].vy + particles[coords2index(i, j - 1, width)].vy) / (dx * dx);

                    float change = delta * (-(vx * vxx + vy * vxy) + (vxxx + vxyy)*viscosity);
                    if(change > max_change){
                        max_change = change;
                    }

                    vx = vx + delta * (-(vx * vxx + vy * vxy) + (vxxx + vxyy)*viscosity);
                    vy = vy + delta * (-(vx * vyx + vy * vyy) + (vyxx + vyyy)*viscosity);

                    newParticles[coords2index(i, j, width)].vx = vx;
                    newParticles[coords2index(i, j, width)].vy = vy;

                }
            }

            printf("%f\n", max_change);

            delete particles;
            particles = newParticles;

        }

};


void drawParticles(sf::RenderWindow& window, Fluid& f){

    sf::RectangleShape rect(sf::Vector2f(1, 1));

    for(int i = 0; i < f.width; i++){
        for(int j = 0; j < f.height; j++){
            Particle& p = f.particles[coords2index(i, j, f.width)];

            float speed = 100*sqrt(p.vx * p.vx + p.vy * p.vy);

            if(speed > 255){
                speed = 255;
            }

            rect.setPosition(i, j);
            rect.setFillColor(sf::Color(speed, speed, speed));

            window.draw(rect);
        }
    }

}

int main(int args, char** argv){

    float WIDTH = 20;
    float HEIGHT = 20;

    Fluid f(WIDTH, HEIGHT, 1);


    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            
            
            f.particles[coords2index(i, j, f.width)].vx = 0;
            f.particles[coords2index(i, j, f.width)].vy = 0;
            f.particles[coords2index(i, j, f.width)].p = 0;

            if(i >= 7 && i <= 13 && j >= 7 && j <= 13){
                f.particles[coords2index(i, j, f.width)].vx = 1;
            }
        }
    }


    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Fluid Simulation");


    for(int i = 0; i < 100000; i++){
        f.physics(0.0001);
        drawParticles(window, f);
        window.display();
    }


}