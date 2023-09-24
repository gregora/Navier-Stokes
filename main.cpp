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


        void diffuse(float delta, float viscosity = 0.1){
            Particle* newParticles = new Particle[width * height];

            for(uint k = 0; k < 20; k++){
                for(uint i = 1; i < width - 1; i++){
                    for(uint j = 1; j < height - 1; j++){
                        
                        Particle& p = newParticles[coords2index(i, j, width)];
                        Particle& p0 = particles[coords2index(i, j, width)];

                        Particle& p1 = newParticles[coords2index(i + 1, j, width)];
                        Particle& p2 = newParticles[coords2index(i - 1, j, width)];
                        Particle& p3 = newParticles[coords2index(i, j + 1, width)];
                        Particle& p4 = newParticles[coords2index(i, j - 1, width)];

                        float vx = p.vx;
                        float vy = p.vy;

                        
                        /*
                        float vxxx = (particles[coords2index(i + 1, j, width)].vx - 2 * particles[coords2index(i + 1, j, width)].vx + 2 * particles[coords2index(i, j, width)].vx + particles[coords2index(i - 1, j, width)].vx) / (dx * dx);
                        float vxyy = (particles[coords2index(i, j + 1, width)].vx - 2 * particles[coords2index(i, j, width)].vx + 2 * particles[coords2index(i, j - 1, width)].vx + particles[coords2index(i, j - 1, width)].vx) / (dx * dx);

                        float vyxx = (particles[coords2index(i + 1, j, width)].vy - 2 * particles[coords2index(i, j, width)].vy + 2 * particles[coords2index(i - 1, j, width)].vy + particles[coords2index(i - 1, j, width)].vy) / (dx * dx);
                        float vyyy = (particles[coords2index(i, j + 1, width)].vy - 2 * particles[coords2index(i, j, width)].vy + 2 * particles[coords2index(i, j - 1, width)].vy + particles[coords2index(i, j - 1, width)].vy) / (dx * dx);

                        vx = vx + delta * ((vxxx + vxyy)*viscosity);
                        vy = vy + delta * ((vyxx + vyyy)*viscosity);
                        */
                        float a = (delta * viscosity) / (dx * dx);
                        vx = p0.vx + a * (p1.vx + p2.vx + p3.vx + p4.vx) / (1 + 4 * a);
                        vy = p0.vy + a * (p1.vy + p2.vy + p3.vy + p4.vy) / (1 + 4 * a);

                        newParticles[coords2index(i, j, width)].vx = vx;
                        newParticles[coords2index(i, j, width)].vy = vy;

                    }
                }
            }

            delete particles;
            particles = newParticles;

        }

        void advect_old(float delta){
            Particle* newParticles = new Particle[width * height];

            for(uint i = 1; i < width - 1; i++){
                for(uint j = 1; j < height - 1; j++){
                    Particle& p = particles[coords2index(i, j, width)];


                    float vx = p.vx;
                    float vy = p.vy;
                    
                    float vxx = (particles[coords2index(i + 1, j, width)].vx - particles[coords2index(i - 1, j, width)].vx) / (2 * dx);
                    float vxy = (particles[coords2index(i, j + 1, width)].vx - particles[coords2index(i, j - 1, width)].vx) / (2 * dx);

                    float vyy = (particles[coords2index(i, j + 1, width)].vy - particles[coords2index(i, j - 1, width)].vy) / (2 * dx);
                    float vyx = (particles[coords2index(i + 1, j, width)].vy - particles[coords2index(i - 1, j, width)].vy) / (2 * dx);

                    vx = vx + delta * (-(vx * vxx + vy * vxy));
                    vy = vy + delta * (-(vx * vyx + vy * vyy));

                    newParticles[coords2index(i, j, width)].vx = vx;
                    newParticles[coords2index(i, j, width)].vy = vy;

                }
            }

            delete particles;
            particles = newParticles;

        }

        void advect(float delta){
            Particle* newParticles = new Particle[width * height];

            for(uint k = 0; k < 20; k++){
                for(uint i = 1; i < width - 1; i++){
                    for(uint j = 1; j < height - 1; j++){
                        Particle& p = newParticles[coords2index(i, j, width)];
                        Particle& p0 = particles[coords2index(i, j, width)];

                        Particle& p1 = newParticles[coords2index(i + 1, j, width)];
                        Particle& p2 = newParticles[coords2index(i - 1, j, width)];

                        Particle& p3 = newParticles[coords2index(i, j + 1, width)];
                        Particle& p4 = newParticles[coords2index(i, j - 1, width)];

                        float vx = p0.vx;
                        float vy = p0.vy;

                        float vxx = (p1.vx - p2.vx) / (2 * dx);
                        float vxy = (p3.vx - p4.vx) / (2 * dx);

                        float vyy = (p3.vy - p4.vy) / (2 * dx);
                        float vyx = (p1.vy - p2.vy) / (2 * dx);
                        
                        vx = (vx - delta*p.vy*vxy)/ (1 + delta*vxx);
                        vy = (vy - delta*p.vx*vyx)/ (1 + delta*vyy);

                        newParticles[coords2index(i, j, width)].vx = vx;
                        newParticles[coords2index(i, j, width)].vy = vy;

                    }
                }
            }
            delete particles;
            particles = newParticles;

        }

        void physics(float delta){

            diffuse(delta);
            advect(delta);

        }

};


void drawParticles(sf::RenderTexture& window, Fluid& f){

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

    float WIDTH = 50;
    float HEIGHT = 50;

    float WINDOW_WIDTH = 1000;
    float WINDOW_HEIGHT = 1000;

    Fluid f(WIDTH, HEIGHT, 1);


    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            
            
            f.particles[coords2index(i, j, f.width)].vx = 0;
            f.particles[coords2index(i, j, f.width)].vy = 0;
            f.particles[coords2index(i, j, f.width)].p = 0;

            if(i >= 20 && i <= 30 && j >= 20 && j <= 30){
                f.particles[coords2index(i, j, f.width)].vx = 1;
            }
        }
    }


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fluid Simulation");
    sf::RenderTexture texture;
    texture.create(WIDTH, HEIGHT);
    texture.setSmooth(true);

    sf::Vector2f scale(WINDOW_WIDTH / WIDTH, WINDOW_HEIGHT / HEIGHT);

    for(int i = 0; i < 100000; i++){
        f.physics(0.01);
        drawParticles(texture, f);
        window.clear();
        sf::Sprite sprite(texture.getTexture());
        sprite.setScale(scale);
        window.draw(sprite);
        window.display();
    }


}