#include <cmath>
#include "particle.h"

void detect_collision(Particle& p1, Particle& p2) {
    /*
    Given two particles, it first
    checks for intersection which is resolved
    by separating the two particles
    then the collision is resolved.

    in the case the boundaries exactly touch
    (unlikely) then collision is resolved directly
    */
    float distance_btw_centers = distance(p1.position, p2.position);
    if (distance_btw_centers < 2*p1.radius) {
        resolve_intersection(p1, p2);
        resolve_collision(p1, p2);
    }
    else if (distance_btw_centers == 2 * p1.radius){
        resolve_collision(p1, p2);
    }
    
}

void resolve_intersection(Particle& p1, Particle& p2) {
    /*
    If particles are intersecting, push each out so
    they are tangential
    Each is pushed out by the same amount

    Likely to be used to handle collisions

    NOTE: 
    1. given that particles are intersecting
    no checks in place to verify above condition
        
    2. Cannot be sure that the positions
    are modified in place. Testing required
    */
    Vector line_of_contact = p1.position - p2.position;
    float distance_intersected = 2 * p1.radius - distance(p1.position, p2.position);
    
    p1.position = p1.position - line_of_contact * (distance_intersected / 2);
    p2.position = p2.position + line_of_contact * (distance_intersected / 2);
}

void resolve_collision(Particle& p1, Particle& p2, float e = 1) {
    /*
    Updates velocities of particles upon collision
    Gets projection of velocity along line of contact
    and updates by reversing the direction of the projection

    TO DO: Incorporate coefficient of restitution

    NOTE: 
    1. given that the particles are tangential
    No checks in place to check tangentiality

    2. Cannot be sure that the positions
    are modified in place. Testing required
    */
    Vector line_of_contact = p1.position = p2.position;
    
    p1.velocity = p1.velocity - projection(p1.velocity, line_of_contact) * 2;
    p2.velocity = p2.velocity + projection(p2.velocity, line_of_contact) * 2;

}