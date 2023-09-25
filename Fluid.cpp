#include "Fluid.h"



int coords2index(int x, int y, int width){

    return y * width + x;

}


Fluid::Fluid(uint width, uint height, float dx){

    this->width = width;
    this->height = height;

    this->dx = dx;

    particles = new Particle[width * height];

}


void Fluid::diffuse(float delta, float viscosity){
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

                float a = (delta * viscosity) / (dx * dx);
                vx = (p0.vx + a * (p1.vx + p2.vx + p3.vx + p4.vx)) / (1 + 4 * a);
                vy = (p0.vy + a * (p1.vy + p2.vy + p3.vy + p4.vy)) / (1 + 4 * a);

                newParticles[coords2index(i, j, width)].vx = vx;
                newParticles[coords2index(i, j, width)].vy = vy;

            }
        }
    }

    delete particles;
    particles = newParticles;

}


void Fluid::advect(float delta){
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


void Fluid::incompressibility(float delta){

    float h = 1.0f / width;

    for(uint i = 1; i < width - 1; i++){
        for(uint j = 1; j < height - 1; j++){

            Particle& p = particles[coords2index(i, j, width)];

            Particle& p1 = particles[coords2index(i + 1, j, width)];
            Particle& p2 = particles[coords2index(i - 1, j, width)];

            Particle& p3 = particles[coords2index(i, j + 1, width)];
            Particle& p4 = particles[coords2index(i, j - 1, width)];

            float div = (p1.vx - p2.vx + p3.vy - p4.vy) / (2 * dx);

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

                p.p = (p1.p + p2.p + p3.p + p4.p - p.div) / (4 * dx * dx);
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

void Fluid::physics(float delta){

    advect(delta);
    //incompressibility(delta); //improves stability
    diffuse(delta);
    incompressibility(delta);

}

float Fluid::energy(){
    float eng = 0;
    for(uint i = 1; i < width - 1; i++){
        for(uint j = 1; j < height - 1; j++){
            Particle& p = particles[coords2index(i, j, width)];
            eng += sqrt(p.vx*p.vx + p.vy*p.vy);
        }
    }

    return eng;
}


void drawParticles(sf::RenderWindow& window, Fluid& f, int block_size, bool render_energy){

    sf::RectangleShape rect(sf::Vector2f(block_size, block_size));
    Arrow arrow;

    for(int i = 0; i < f.width; i++){
        for(int j = 0; j < f.height; j++){
            Particle& p = f.particles[coords2index(i, j, f.width)];

            float speed = 50*sqrt(p.vx * p.vx + p.vy * p.vy);
            
            if(speed > 255){
                speed = 255;
            }

            float p_color = 125 + 50*p.p;

            if(p_color > 255){
                p_color = 255;
            }

            if (p_color < 0)
            {
                p_color = 0;
            }
            

            rect.setPosition(i * block_size, j * block_size);
            rect.setFillColor(sf::Color(p_color, p_color, p_color));
            window.draw(rect);

            float ang = atan2(p.vy, p.vx);

            arrow.setPosition(i * block_size + block_size/2, j * block_size + block_size/2);
            ang = 90 + ang * 180 / M_PI;
            arrow.setRotation(ang);
            arrow.setOpacity(speed);
            if(speed > 100){
                speed = 100;
            }
            arrow.setScale(speed / 100, speed / 100);
            window.draw(arrow);

        }
    }


    if(render_energy){
        //total energy as text
        float eng = f.energy();

        sf::Font font;
        font.loadFromFile("fonts/Prototype.ttf");

        sf::Text text;
        text.setFont(font);
        text.setString("Total energy: " + std::to_string((int) eng));

        text.setCharacterSize(18);
        text.setFillColor(sf::Color::Black);
        text.setStyle(sf::Text::Bold);
        text.setPosition(10, 10);

        window.draw(text);
    }

}
