#ifndef PARTICLE_H 
#define PARTICLE_H

#include "vector.h"

struct Particle {
    Vector position = Vector{0, 0};
    Vector velocity = Vector{0, 0};
    Vector acceleration = Vector{0, -9.81};

    double radius = 10;
    double mass = 1;
};

void detect_collision(Particle& p1, Particle& p2);

void resolve_collision(Particle& p1, Particle& p2, double e = 1);

void resolve_intersection(Particle& p1, Particle& p2);

void resolve_collision_wall(Particle& p, int flag) ;

void display_details(Particle p);

#endif 