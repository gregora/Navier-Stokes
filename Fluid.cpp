#include "Fluid.h"
#include <thread>
#include <chrono>


int coords2index(int x, int y, int width){

    return y * width + x;

}


Fluid::Fluid(uint width, uint height, float dx){

    this->width = width;
    this->height = height;

    this->dx = dx;

    particles = new Particle[width * height];

    this -> set_boundaries = set_bnd;

}

void Fluid::diffuse_iteration(Particle* newParticles, float delta, float viscosity, uint i, uint j){
    Particle& p = newParticles[coords2index(i, j, width)];
    Particle& p0 = particles[coords2index(i, j, width)];

    Particle& p1 = newParticles[coords2index(i + 1, j, width)];
    Particle& p2 = newParticles[coords2index(i - 1, j, width)];
    Particle& p3 = newParticles[coords2index(i, j + 1, width)];
    Particle& p4 = newParticles[coords2index(i, j - 1, width)];

    float vx = p.vx;
    float vy = p.vy;

    float smoke = p0.smoke;

    float a = (delta * viscosity) / (dx * dx);
    vx = (p0.vx + a * (p1.vx + p2.vx + p3.vx + p4.vx)) / (1 + 4 * a);
    vy = (p0.vy + a * (p1.vy + p2.vy + p3.vy + p4.vy)) / (1 + 4 * a);
    smoke = (p0.smoke + a * (p1.smoke + p2.smoke + p3.smoke + p4.smoke)) / (1 + 4 * a);

    p.vx = vx;
    p.vy = vy;
    p.smoke = smoke;

    p.Fx = p0.Fx;
    p.Fy = p0.Fy;
}



void Fluid::advect_iteration(Particle* newParticles, float delta, uint i, uint j){

    // LAX METHOD FOR SOLVING ADVECTION EQUATION
    // this method is so far unstable

    /*
    Particle& p0 = particles[coords2index(i, j, width)];

    float vx = p0.vx;
    float vy = p0.vy;


    Particle& p1 = particles[coords2index(i + 1, j, width)];
    Particle& p2 = particles[coords2index(i - 1, j, width)];

    Particle& p3 = particles[coords2index(i, j + 1, width)];
    Particle& p4 = particles[coords2index(i, j - 1, width)];


    Particle& p = newParticles[coords2index(i, j, width)];

    p.vx = p0.vx - p.vx * delta / dx * (p0.vx - p2.vx) - p.vy * delta / dx * (p0.vx - p4.vx);
    p.vy = p0.vy - p.vx * delta / dx * (p0.vy - p2.vy) - p.vy * delta / dx * (p0.vy - p4.vy);

    p.smoke = p0.smoke - p.vx * delta / dx * (p0.smoke - p2.smoke) - p.vy * delta / dx * (p0.smoke - p4.smoke);
    */


    // SEMI-LAGRANGIAN METHOD FOR SOLVING ADVECTION EQUATION
    
    Particle& p0 = particles[coords2index(i, j, width)];

    float vx = p0.vx;
    float vy = p0.vy;

    float x = i - delta * vx / dx;
    float y = j - delta * vy / dx;

    if(x < 0.5){
        x = 0.5;
    }

    if(x > width - 1.5){
        x = width - 1.5;
    }

    if(y < 0.5){
        y = 0.5;
    }

    if(y > height - 1.5){
        y = height - 1.5;
    }

    float x0 = (uint) x;
    float y0 = (uint) y;

    float x1 = x0 + 1;
    float y1 = y0 + 1;

    float k1 = x - x0;
    float k2 = 1 - k1;
    float k3 = y - y0;
    float k4 = 1 - k3;

    Particle& p1 = particles[coords2index(x0, y0, width)];
    Particle& p2 = particles[coords2index(x1, y0, width)];
    Particle& p3 = particles[coords2index(x0, y1, width)];
    Particle& p4 = particles[coords2index(x1, y1, width)];

    Particle& p = newParticles[coords2index(i, j, width)];

    p.vx = k2 * (k4 * p1.vx + k3 * p3.vx) + k1 * (k4 * p2.vx + k3 * p4.vx);
    p.vy = k2 * (k4 * p1.vy + k3 * p3.vy) + k1 * (k4 * p2.vy + k3 * p4.vy);

    p.smoke = k2 * (k4 * p1.smoke + k3 * p3.smoke) + k1 * (k4 * p2.smoke + k3 * p4.smoke);


}


void Fluid::external_forces(float delta){
    
    for(uint i = 1; i < width - 1; i++){
        for(uint j = 1; j < height - 1; j++){
            Particle& p = particles[coords2index(i, j, width)];

            p.vx += delta * p.Fx;
            p.vy += delta * p.Fy;
        }
    }
}

void Fluid::pressure_iteration(float delta, uint i, uint j){
    Particle& p = particles[coords2index(i, j, width)];

    Particle& p1 = particles[coords2index(i + 1, j, width)];
    Particle& p2 = particles[coords2index(i - 1, j, width)];

    Particle& p3 = particles[coords2index(i, j + 1, width)];
    Particle& p4 = particles[coords2index(i, j - 1, width)];

    p.p = (p1.p + p2.p + p3.p + p4.p - p.div * dx * dx / delta) / 4;
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

    set_boundaries(particles, width, height, 3);
    set_boundaries(particles, width, height, 4);

    for(uint k = 0; k < gs_iters; k++){
        std::thread threads_array[threads];

        for(uint t = 0; t < threads; t++){
            threads_array[t] = std::thread(&Fluid::pressure_sector, this, delta, t * width / threads, (t + 1) * width / threads);
        }

        for(uint t = 0; t < threads; t++){
            threads_array[t].join();
        }

        set_boundaries(particles, width, height, 4);

    }


    for(uint i = 1; i < width - 1; i++){
        for(uint j = 1; j < height - 1; j++){
            Particle& p = particles[coords2index(i, j, width)];

            Particle& p1 = particles[coords2index(i + 1, j, width)];
            Particle& p2 = particles[coords2index(i - 1, j, width)];

            Particle& p3 = particles[coords2index(i, j + 1, width)];
            Particle& p4 = particles[coords2index(i, j - 1, width)];

            p.vx = p.vx - delta*(p1.p - p2.p) / (2 * dx);
            p.vy = p.vy - delta*(p3.p - p4.p) / (2 * dx);
        }
    }

    set_boundaries(particles, width, height, 1);
    set_boundaries(particles, width, height, 2);
    set_boundaries(particles, width, height, 5);

}

void Fluid::physics(float delta){

    //measure time of physics
    auto start = std::chrono::high_resolution_clock::now();

    external_forces(delta);
    advect(delta);
    diffuse(delta);
    incompressibility(delta);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    //printf("Physics time: %f\n", elapsed.count());
}

float Fluid::energy(){
    float eng = 0;
    for(uint i = 1; i < width - 1; i++){
        for(uint j = 1; j < height - 1; j++){
            Particle& p = particles[coords2index(i, j, width)];
            eng += p.vx*p.vx + p.vy*p.vy;
        }
    }

    return eng;
}



void set_bnd(Particle* particles, uint width, uint height, uint identifier){

    /*
    IDENTIFIERS:
    1 - velocity x
    2 - velocity y
    3 - divergence
    4 - pressure
    5 - smoke
    */

    //top and bottom
    for(uint i = 1; i < width - 1; i++){

        if(identifier == 1){
            //particles[coords2index(i, 0, width)].vx = particles[coords2index(i, 1, width)].vx;
            //particles[coords2index(i, height - 1, width)].vx = particles[coords2index(i, height - 2, width)].vx;
            particles[coords2index(i, 0, width)].vx = 0;
            particles[coords2index(i, height - 1, width)].vx = 0;
        }

        if(identifier == 2){
            particles[coords2index(i, 0, width)].vy = -particles[coords2index(i, 1, width)].vy;
            particles[coords2index(i, height - 1, width)].vy = -particles[coords2index(i, height - 2, width)].vy;
        }

        if(identifier == 3){
            particles[coords2index(i, 0, width)].div = particles[coords2index(i, 1, width)].div;
            particles[coords2index(i, height - 1, width)].div = particles[coords2index(i, height - 2, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(i, 0, width)].p = particles[coords2index(i, 1, width)].p;
            particles[coords2index(i, height - 1, width)].p = particles[coords2index(i, height - 2, width)].p;        
        }
    }

    //left and right
    for(uint j = 1; j < height - 1; j++){

        if(identifier == 1){
            particles[coords2index(0, j, width)].vx = -particles[coords2index(1, j, width)].vx;
            particles[coords2index(width - 1, j, width)].vx = -particles[coords2index(width - 2, j, width)].vx;
        }

        if(identifier == 2){
            //particles[coords2index(0, j, width)].vy = particles[coords2index(1, j, width)].vy;
            //particles[coords2index(width - 1, j, width)].vy = particles[coords2index(width - 2, j, width)].vy;
            particles[coords2index(0, j, width)].vy = 0;
            particles[coords2index(width - 1, j, width)].vy = 0;
        }

        if(identifier == 3){
            particles[coords2index(0, j, width)].div = particles[coords2index(1, j, width)].div;
            particles[coords2index(width - 1, j, width)].div = particles[coords2index(width - 2, j, width)].div;
        }

        if(identifier == 4){
            particles[coords2index(0, j, width)].p = particles[coords2index(1, j, width)].p;
            particles[coords2index(width - 1, j, width)].p = particles[coords2index(width - 2, j, width)].p;
        }
    }


}


void drawParticles(sf::RenderWindow& window, Fluid& f, int block_size, bool render_energy, bool render_velocities){

    sf::RectangleShape rect(sf::Vector2f(block_size, block_size));
    Arrow arrow;

    for(int i = 0; i < f.width; i++){
        for(int j = 0; j < f.height; j++){
            Particle& p = f.particles[coords2index(i, j, f.width)];

            float speed = 70*sqrt(p.vx * p.vx + p.vy * p.vy);
            
            if(speed > 255){
                speed = 255;
            }

            //float p_color = 125 + 50*p.p;
            float p_color = 255*p.smoke;

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
            if(render_velocities){
                arrow.setOpacity(speed);
            }else{
                arrow.setOpacity(0);
            }
            if(speed > 100){
                speed = 100;
            }
            arrow.setScale(block_size * speed / 1000, block_size * speed / 1000);
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
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(10, 10);

        window.draw(text);
    }

}




void Fluid::diffuse_sector(Particle* newParticles, float delta, float viscosity, uint start, uint end){

    for(uint i = start; i < end; i++){

        if(i == 0 || i == width - 1){
            continue;
        }

        for(uint j = 1; j < height - 1; j++){
            diffuse_iteration(newParticles, delta, viscosity, i, j);
        }
    }

}


void Fluid::diffuse(float delta, float viscosity){
    Particle* newParticles = new Particle[width * height];

    std::thread threads_array[threads];
    for(uint k = 0; k < gs_iters; k++){       
        for(uint t = 0; t < threads; t++){
            threads_array[t] = std::thread(&Fluid::diffuse_sector, this, newParticles, delta, viscosity, t * width / threads, (t + 1) * width / threads);
        }        

        for(uint t = 0; t < threads; t++){
            threads_array[t].join();
        }

        set_boundaries(newParticles, width, height, 1);
        set_boundaries(newParticles, width, height, 2);
        set_boundaries(newParticles, width, height, 5);


    }

    delete particles;
    particles = newParticles;

}


void Fluid::advect_sector(Particle* newParticles, float delta, uint start, uint end){

    for(uint i = start; i < end; i++){

        if(i == 0 || i == width - 1){
            continue;
        }

        for(uint j = 1; j < height - 1; j++){
            advect_iteration(newParticles, delta, i, j);
        }
    }

}

void Fluid::advect(float delta){
    Particle* newParticles = new Particle[width * height];

    std::thread threads_array[threads];

    for(uint t = 0; t < threads; t++){
        threads_array[t] = std::thread(&Fluid::advect_sector, this, newParticles, delta, t * width / threads, (t + 1) * width / threads);
    }

    for(uint t = 0; t < threads; t++){
        threads_array[t].join();
    }

    set_boundaries(newParticles, width, height, 1);
    set_boundaries(newParticles, width, height, 2);
    set_boundaries(newParticles, width, height, 5);


    delete particles;
    particles = newParticles;

}

void Fluid::pressure_sector(float delta, uint start, uint end){

    for(uint i = start; i < end; i++){

        if(i == 0 || i == width - 1){
            continue;
        }

        for(uint j = 1; j < height - 1; j++){
            pressure_iteration(delta, i, j);
        }
    }

}