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

int coords2index(int x, int y, int width);

class Fluid {

    public:
        uint width;
        uint height;
        float dx;
        
        uint gs_iters = 20; // Number of Gauss-Seidel iterations

        Particle* particles;

        Fluid(uint width, uint height, float dx);


        void diffuse(float delta, float viscosity = 0.1);

        void advect(float delta);

        void incompressibility(float delta);

        void physics(float delta);

        float energy();

};


void drawParticles(sf::RenderWindow& window, Fluid& f, int block_size = 20, bool render_energy = true);