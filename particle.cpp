#include <cmath>
#include "particle.h"

bool detect_collision(Particle& p1, Particle& p2) {
    /*
    Returns True if two particles are colliding
    if distance between two particles is equal to distance 
    between centers, collision is detected

    Note: works only if distance is exactly 2*r
    Likely case: frame oversteps and particles intersect

    TO DO: Make distance a vector.cpp function and create a 
    case handler in particle
    */
    float distance = pow(pow(p1.position.x - p2.position.x, 2) + pow(p1.position.y - p2.position.y, 2), 0.5);
    if (distance == 2*p1.radius) {
        return true;
    }
    return false;
}

void resolve_intersection(Particle& p1, Particle& p2) {
    /*
    If particles are intersecting, push each out so
    they are tangential
    Each is pushed out by the same amount

    Likely to be used to handle collisions

    TO DO: Again use vector's distance and master collision handler
    */
    float distance = pow(pow(p1.position.x - p2.position.x, 2) + pow(p1.position.y - p2.position.y, 2), 0.5);
    Vector line_of_contact = p1.position - p2.position;
    if (distance < 2*p1.radius) {
        float distance_intersected = 2 * p1.radius - distance;
        p1.position = p1.position - line_of_contact * (distance_intersected / 2);
        p2.position = p2.position + line_of_contact * (distance_intersected / 2);
    }
}

void resolve_collision(Particle& p1, Particle& p2, float e = 1) {
    /*
    Updates velocities of particles upon collision
    Gets projection of velocity along line of contact
    and updates by reversing the direction of the projection

    TO DO: Incorporate coefficient of restitution
    */
    Vector line_of_contact = p1.position = p2.position;
    p1.velocity = p1.velocity - projection(p1.velocity, line_of_contact) * 2;
    p2.velocity = p2.velocity + projection(p2.velocity, line_of_contact) * 2;

}