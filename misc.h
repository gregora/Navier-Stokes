#if !defined _MISC_H
#define	_MISC_H 1

#include <SFML/Graphics.hpp>
#include "Fluid.h"

class ExampleFluid1 : public Fluid {
    public:
        ExampleFluid1(uint width, uint height, float dx) : Fluid(width, height, dx) {};
        void set_boundaries(Particle* particles, uint width, uint height, uint identifier);
};

class ExampleFluid2 : public Fluid {
    public:
        ExampleFluid2(uint width, uint height, float dx) : Fluid(width, height, dx) {};
        void set_boundaries(Particle* particles, uint width, uint height, uint identifier);
};

class TunnelFluid : public Fluid {
    public:
        TunnelFluid(uint width, uint height, float dx) : Fluid(width, height, dx) {};
        void set_boundaries(Particle* particles, uint width, uint height, uint identifier);
};


void postProcessingTunnel(sf::RenderWindow& window, uint block_size);

#endif