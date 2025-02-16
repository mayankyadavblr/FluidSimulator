#include "frame.h"
#include <cmath>
#include <chrono>
#include <iostream>

void update_particle(Particle& p, double dt){
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
    // std::cout << "particle position: " << p.position.x <<","<< p.position.y<<std::endl;

    //p.acceleration = p.acceleration; NO CHANGE NEEDED

}

void update_frame(Frame& frame){
    /*
    Update all the particles in a frame
    Must have calls to check for collisions
    Essentially: the "main" function

    TO DO: entire function
    */
    int frame_count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    
    while (frame_count < 120){
        for (size_t i = 0; i < frame.all_particles.size() - 1; ++i) {
            for (size_t j = i + 1; j < frame.all_particles.size(); ++j) {
                detect_collision(frame.all_particles[i], frame.all_particles[j]);
            }
        }

        check_boundaries(frame);
        
        for (size_t i = 0; i < frame.all_particles.size(); ++i){
            update_particle(frame.all_particles[i], frame.dt);
        }
        frame_count++;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    std::cout << microseconds.count() << "us\n";

}

void check_boundaries(Frame& frame){
    for (size_t i = 0; i < frame.number_of_particles; ++i) {
        Particle& p = frame.all_particles[i];
        //RIGHT
        if (p.position.x > frame.tr.x - 2*p.radius) {
            p.position.x = frame.tr.x - 2*p.radius;
            p.velocity.x = - p.velocity.x;
        }
        //LEFT
        if (p.position.x < frame.bl.x){
            p.position.x = frame.bl.x;
            p.velocity.x = - p.velocity.x;
        }
        //TOP
        if (-p.position.y < frame.tr.y ) {
            // std::cout<<"top collision"<<std::endl;
            p.position.y = frame.tr.y;
            p.position.y = -p.position.y;
            p.velocity.y = - p.velocity.y;
        }
        //BOTTOM
        if (-p.position.y > frame.bl.y - 2*p.radius){
            p.position.y = frame.bl.y - 2*p.radius;
            p.position.y = -p.position.y;
            p.velocity.y = - p.velocity.y;
        }
    }
}
