#include <SFML/Graphics.hpp>
#include "stdio.h"
#include <string.h>
#include <string>
#include "math.h"
#include <thread>
#include <chrono>
#include "Arrow.h"

struct Particle {

    float vx = 0;
    float vy = 0;
    
    float div = 0;
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


        void incompressibility(float delta){

            float h = 1.0f / width;

            for(uint i = 1; i < width - 1; i++){
                for(uint j = 1; j < height - 1; j++){

                    Particle& p = particles[coords2index(i, j, width)];

                    Particle& p1 = particles[coords2index(i + 1, j, width)];
                    Particle& p2 = particles[coords2index(i - 1, j, width)];

                    Particle& p3 = particles[coords2index(i, j + 1, width)];
                    Particle& p4 = particles[coords2index(i, j - 1, width)];

                    float div = - (p1.vx - p2.vx + p3.vy - p4.vy) / (2 * dx);

                    p.div = div;
                    p.p = 0;

                }
            }

            for(uint k = 0; k < 20; k++){
                for(uint i = 1; i < width - 1; i++){
                    for(uint j = 1; j < height - 1; j++){
                        Particle& p = particles[coords2index(i, j, width)];

                        Particle& p1 = particles[coords2index(i + 1, j, width)];
                        Particle& p2 = particles[coords2index(i - 1, j, width)];

                        Particle& p3 = particles[coords2index(i, j + 1, width)];
                        Particle& p4 = particles[coords2index(i, j - 1, width)];

                        p.p = (p1.p + p2.p + p3.p + p4.p + p.div) / 4;
                    }
                }
            }


            for(uint i = 1; i < width - 1; i++){
                for(uint j = 1; j < height - 1; j++){
                    Particle& p = particles[coords2index(i, j, width)];

                    Particle& p1 = particles[coords2index(i + 1, j, width)];
                    Particle& p2 = particles[coords2index(i - 1, j, width)];

                    Particle& p3 = particles[coords2index(i, j + 1, width)];
                    Particle& p4 = particles[coords2index(i, j - 1, width)];

                    //printf("%f\n", delta*(p1.p - p2.p) / (2 * dx));
                    //printf("%f\n", delta*(p3.p - p4.p) / (2 * dx));

                    p.vx = p.vx - delta*(p1.p - p2.p) / (2 * dx);
                    p.vy = p.vy - delta*(p3.p - p4.p) / (2 * dx);
                }
            }

        }

        void physics(float delta){

            diffuse(delta);
            advect(delta);
            incompressibility(delta);

        }

};


void drawParticles(sf::RenderTexture& window, Fluid& f, int block_size = 20){

    sf::RectangleShape rect(sf::Vector2f(block_size, block_size));
    Arrow arrow;

    for(int i = 0; i < f.width; i++){
        for(int j = 0; j < f.height; j++){
            Particle& p = f.particles[coords2index(i, j, f.width)];

            float speed = 100*sqrt(p.vx * p.vx + p.vy * p.vy);

            if(speed > 255){
                speed = 255;
            }

            rect.setPosition((j) * block_size, (i) * block_size);
            rect.setFillColor(sf::Color(speed, speed, speed));
            window.draw(rect);

            float ang = atan2(p.vy, p.vx);

            arrow.setPosition((j) * block_size + block_size/2, (i) * block_size + block_size/2);
            ang = 180 - ang * 180 / M_PI;
            arrow.setRotation(ang);
            if(speed > 100){
                speed = 100;
            }
            arrow.setScale(speed / 100, speed / 100);
            window.draw(arrow);

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
    texture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
    texture.setSmooth(true);


    for(int i = 0; i < 100000; i++){
        f.physics(0.001);
        drawParticles(texture, f, 20);
        window.clear();
        sf::Sprite sprite(texture.getTexture());
        window.draw(sprite);
        window.display();
    }


}