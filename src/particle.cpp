#include <cmath>
#include "particle.h"
#include <iostream>
#include "frame.h"

void detect_collision(Particle* p1, Particle* p2, double dt) {
    /*
    Given two particles, it first
    checks for intersection which is resolved
    by separating the two particles
    then the collision is resolved.

    in the case the boundaries exactly touch
    (unlikely) then collision is resolved directly

    TODO:
    1. handle hard coding of 'dt'
    */
    // dt = 1.00/60.00;
    double distance_btw_centers = distance(p1->position, p2->position);
    if (distance_btw_centers < p1->radius + p2->radius) {
        
        double collision_time = resolve_intersection(p1, p2, dt);
        // resolve_intersection(p1, p2, dt);
        resolve_collision(p1, p2);
        
        // update_particle(p1, dt - collision_time);
        // update_particle(p2, dt - collision_time);
    }
    else if (distance_btw_centers == p1->radius + p2->radius){
        resolve_collision(p1, p2);
    }
    
}

double resolve_intersection(Particle* p1, Particle* p2, double dt) {
    /*
    If particles are intersecting, push each out so
    they are tangential
    Each is pushed out by the same amount

    Likely to be used to handle collisions

    NOTE: 
    1. given that particles are intersecting
    no checks in place to verify above condition

    TODO:
    1. refactor to include dt
    2. refactor to handle N
        
    */
//    double dt = 1.00/60.00; // Refactor code to not have to do this

    double collision_time = 0.0;
    // Particle p1_prev = inverse_update_particle(*p1, dt);
    // Particle p2_prev = inverse_update_particle(*p2, dt);

    // collision_time = linear_interpolate_collision(p1_prev, p2_prev, dt); // Refactor to not have to hard code N
    
    // p1->position = p1_prev.position + p1_prev.velocity * collision_time + p1->acceleration * 0.5 * collision_time;
    // p1->velocity = p1_prev.velocity + p1_prev.acceleration * collision_time;
    // p2->position = p2_prev.position + p2_prev.velocity * collision_time + p1->acceleration * 0.5 * collision_time;
    // p2->velocity = p2_prev.velocity + p2_prev.acceleration * collision_time;

    Vector line_of_contact = p1->position - p2->position;
    line_of_contact = line_of_contact / magnitude(line_of_contact);
    
    double distance_intersected = p1->radius + p2->radius - distance(p1->position, p2->position);

    p1->position = p1->position + line_of_contact * (distance_intersected / 2.00);
    p2->position = p2->position - line_of_contact * (distance_intersected / 2.00);

    return collision_time;

}

double linear_interpolate_collision(Particle p1, Particle p2, double dt, double N){
    /*
    |(p1.position + p1.velocity * t) - (p2.position + p2.velocity * t)| = p1.radius + p2.radius
    in other words:
    distance between centers at time 't' is sum of radii 

    two choices to solve:
    1. linear interpolation: divide dt into further N timesteps
    check each sub timestep for a collision, report first one

    2. Solve the equation
    */
    // double dt = 1.00/60.00;
    double new_dt = dt/N;
    if (distance(p1.position, p2.position) < p1.radius + p2.radius){
        return dt;
    }
    for (int i=1; i < N+1; i++){
        p1.position = p1.position + p1.velocity * new_dt + p1.acceleration * 0.5 * new_dt;
        p1.velocity = p1.velocity + p1.acceleration * new_dt;
        
        p2.position = p2.position + p2.velocity * new_dt + p2.acceleration * 0.5 * new_dt;
        p2.velocity = p2.velocity + p2.acceleration * new_dt;

        if (distance(p1.position, p2.position) < p1.radius + p2.radius){
            return i*new_dt;
        }

    }
    return dt;
}

void resolve_collision(Particle* p1, Particle* p2, double e) {
    /*
    Updates velocities of particles upon collision
    Gets projection of velocity along line of contact
    and updates by reversing the direction of the projection

    TO DO: Incorporate coefficient of restitution

    NOTE: 
    1. given that the particles are tangential
    No checks in place to check tangentiality

    */

    Vector line_of_contact = p1->position - p2->position;
    Vector speed_along_loc_p1 = projection(p1->velocity, line_of_contact);
    Vector speed_along_loc_p2 = projection(p2->velocity, line_of_contact);
    
    p1->velocity = p1->velocity - speed_along_loc_p1 + speed_along_loc_p1 * (p1->mass - e*p2->mass)/(p1->mass + p2->mass) + speed_along_loc_p2 * ((1+e)*p2->mass)/(p1->mass + p2->mass);
    p2->velocity = p2->velocity - speed_along_loc_p2 + speed_along_loc_p2 * (p2->mass - e*p1->mass)/(p1->mass + p2->mass) + speed_along_loc_p1 * ((1+e)*p1->mass)/(p1->mass + p2->mass);
 
}

void display_details(Particle p) {
    std::cout << "Position: "<< p.position.x << ", " << p.position.y<<std::endl;
    std::cout << "Velocity: "<< p.velocity.x << ", " << p.velocity.y<<std::endl;
    std::cout<<std::endl;
}