#include "frame.h"
#include <cmath>

void update_particle(Particle& p, float dt){
    /*
    Updates a particle's position
    velocity and acceleration
    NOTE: acceleration is constant - gravity

    Formulae:
    x = ut + 1/2 at^2
    v = u + at
    */
    Vector acceleration_projection = projection(p.acceleration, p.velocity);

    p.position = p.position + p.velocity * dt + p.acceleration * 0.5 * pow(dt, 2);
    p.velocity = p.velocity + p.acceleration * dt;
    //p.acceleration = p.acceleration; NO CHANGE NEEDED

}

void update_frame(Frame& frame){
    /*
    Update all the particles in a frame
    Must have calls to check for collisions
    Essentially: the "main" function

    TO DO: entire function
    */
}