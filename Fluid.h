#if !defined _FLUID_H
#define	_FLUID_H 1


#include <SFML/Graphics.hpp>
#include "stdio.h"
#include <string.h>
#include <string>
#include "math.h"
#include <thread>
#include <chrono>
#include "Arrow.h"



class Particle {
    public:
        //velocity field
        float vx = 0;
        float vy = 0;
        
        //divergence field
        float div = 0;
        //pressure field
        float p = 0;

        //external forces field
        float Fx = 0;
        float Fy = 0;

        //smoke density field
        float smoke = 0;

};

int coords2index(int x, int y, int width);

class Fluid {

    public:
        uint width;
        uint height;
        float dx;

        bool show_warnings = false;

        uint threads = 1; // Number of threads to use
        
        uint gs_iters = 20; // Number of Gauss-Seidel iterations

        Particle* particles;

        Fluid(uint width, uint height, float dx);
        ~Fluid();

        void diffuse_iteration(Particle* newParticles, float delta, float viscosity, uint i, uint j);
        void diffuse_sector(Particle* newParticles, float delta, float viscosity, uint start, uint end);
        void diffuse(float delta, float viscosity = 0.1);

        void advect_iteration(Particle* newParticles, float delta, uint i, uint j);
        void advect_sector(Particle* newParticles, float delta, uint start, uint end);
        void advect(float delta);

        void external_forces(float delta);

        void pressure_iteration(float delta, uint i, uint j);
        void pressure_sector(float delta, uint start, uint end);
        void incompressibility(float delta);

        void physics(float delta);

        virtual void set_boundaries(Particle* particles, uint width, uint height, uint identifier);

        float energy();
        float max_delta();
        float max_velocity();

        void drawParticles(sf::RenderTarget& target, int block_size, bool render_energy, bool render_velocities, bool render_pressure);


};


#endif