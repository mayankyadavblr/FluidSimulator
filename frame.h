#ifndef FRAME_H 
#define FRAME_H
#include <vector>

#include "particle.h"

struct Frame {
    float dt; // Set to inverse of desired frame rate
    int number_of_particles;
    std::vector<Particle> all_particles;

    //TO DO: make an initializer for ease of testing  
};

void update_particle(Particle& p, float dt);

void update_frame(Frame& frame);

#endif 