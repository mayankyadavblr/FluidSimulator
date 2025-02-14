#ifndef FRAME_H 
#define FRAME_H
#include <vector>

#include "particle.h"

struct Frame {
    double dt; // Set to inverse of desired frame rate
    int number_of_particles;
    std::vector<Particle> all_particles;

    //TO DO: make an initializer for ease of testing  
};

void update_particle(Particle& p, double dt);

void update_frame(Frame& frame);

#endif 