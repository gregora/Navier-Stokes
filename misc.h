#if !defined _MISC_H
#define	_MISC_H 1

#include <SFML/Graphics.hpp>
#include "Fluid.h"

void set_bnd2(Particle* particles, uint width, uint height, uint identifier);
void tunnel_bnd(Particle* particles, uint width, uint height, uint identifier);

void postProcessingTunnel(sf::RenderWindow& window, uint block_size);

#endif