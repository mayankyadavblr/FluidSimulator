#ifndef PARTICLE_H 
#define PARTICLE_H

#include "vector.h"

struct Particle {
    Vector position = Vector{0, 0};
    Vector velocity = Vector{0, 0};
    float radius = 1;
};

bool detect_collision(Particle& p1, Particle& p2);

void resolve_intersection(Particle& p1, Particle& p2);

#endif 