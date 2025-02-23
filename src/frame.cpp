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

    //p.acceleration = p.acceleration; NO CHANGE NEEDED

}

Particle inverse_update_particle(Particle p, double dt){
    /*
    Backtracks a particle's position
    velocity and acceleration to previous timestep
    NOTE: acceleration is constant - gravity

    Formulae:
    x0 = x - ut - 1/2 at^2
    u = v - at
    */
    p.position = p.position - p.velocity * dt - p.acceleration * 0.5 * pow(dt, 2);
    p.velocity = p.velocity - p.acceleration * dt;
    return p;
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
        for (size_t i = 0; i < frame.number_of_particles - 1; ++i) {
            for (size_t j = i + 1; j < frame.number_of_particles; ++j) {
                detect_collision(frame.all_particles[i], frame.all_particles[j], frame.dt);
            }
        }

        check_boundaries(frame);
        
        for (size_t i = 0; i < frame.number_of_particles; ++i){
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
        if (p.position.x > frame.tr.x - p.radius) {
            p.position.x = frame.tr.x - p.radius;
            p.velocity.x = - p.velocity.x;
        }
        //LEFT
        if (p.position.x < frame.bl.x + p.radius){
            p.position.x = frame.bl.x + p.radius;
            p.velocity.x = - p.velocity.x;
        }
        //TOP
        if (-p.position.y < frame.tr.y + p.radius) {
            // std::cout<<"top collision"<<std::endl;
            p.position.y = frame.tr.y + p.radius;
            p.position.y = -p.position.y;
            p.velocity.y = - p.velocity.y;
        }
        //BOTTOM
        if (-p.position.y > frame.bl.y - p.radius){
            p.position.y = frame.bl.y - p.radius;
            p.position.y = -p.position.y;
            p.velocity.y = - p.velocity.y;
        }
    }
}

void subdivide_frame(Frame& frame){
    // Hard set dt, max_number_of_particles, number_of_particles
    frame.topLeft = new Frame;
    frame.topLeft->dt = frame.dt; frame.topLeft->max_number_of_particles = frame.max_number_of_particles; frame.topLeft->number_of_particles = frame.number_of_particles;
    frame.topLeft->boundary = Rectangle{
        frame.boundary.center + Vector{-frame.boundary.width/2.00, frame.boundary.height/2.00},
        frame.boundary.width/2.00,
        frame.boundary.height/2.00
    };

    frame.topRight = new Frame;
    frame.topRight->dt = frame.dt; frame.topRight->max_number_of_particles = frame.max_number_of_particles; frame.topRight->number_of_particles = frame.number_of_particles;
    frame.topRight->boundary = Rectangle{
        frame.boundary.center + Vector{frame.boundary.width/2.00, frame.boundary.height/2.00},
        frame.boundary.width/2.00,
        frame.boundary.height/2.00
    };

    frame.bottomLeft = new Frame;
    frame.bottomLeft->dt = frame.dt; frame.bottomLeft->max_number_of_particles = frame.max_number_of_particles; frame.bottomLeft->number_of_particles = frame.number_of_particles;
    frame.bottomLeft->boundary = Rectangle{
        frame.boundary.center + Vector{-frame.boundary.width/2.00, -frame.boundary.height/2.00},
        frame.boundary.width/2.00,
        frame.boundary.height/2.00
    };

    frame.bottomRight = new Frame;
    frame.bottomRight->dt = frame.dt; frame.bottomRight->max_number_of_particles = frame.max_number_of_particles; frame.bottomRight->number_of_particles = frame.number_of_particles;
    frame.bottomRight->boundary = Rectangle{
        frame.boundary.center + Vector{frame.boundary.width/2.00, -frame.boundary.height/2.00},
        frame.boundary.width/2.00,
        frame.boundary.height/2.00
    };
}

void insert_point(Particle& p, Frame& frame){
    if (!contains(p.position, frame.boundary)){
        return;
    }
    if (frame.number_of_particles < frame.max_number_of_particles) {
        frame.all_particles.push_back(p);
        frame.number_of_particles++;
    }
    else {
        if (! frame.divided) {
            subdivide_frame(frame);
            frame.divided = true;
        }
        insert_point(p, *frame.topLeft);
        insert_point(p, *frame.topRight);
        insert_point(p, *frame.bottomLeft);
        insert_point(p, *frame.bottomRight);
    }

}

bool contains(Vector p, Rectangle boundary) {
    if (p.x > boundary.center.x - boundary.width &&
        p.x < boundary.center.x + boundary.width &&
        -p.y < boundary.center.y + boundary.height &&
        -p.y > boundary.center.y - boundary.height){
        return true;
    }
    return false;
}

bool intersects(Rectangle r1, Rectangle r2) {
    if (r1.center.x - r1.width > r2.center.x + r2.width ||
        r1.center.x + r1.width < r2.center.x - r2.width ||
        r1.center.y - r1.height > r2.center.y + r2.height ||
        r1.center.y + r1.height < r2.center.y - r2.height) {
            return false;
        }
    return true;
}

void query(Rectangle r, Frame& frame, std::vector<Particle>& found_particles) {
    std::cout<<frame.boundary.width<<std::endl;
    if (!intersects(r, frame.boundary)){
        return;
    }
    for (int i=0; i<frame.number_of_particles; i++){
        if (contains(frame.all_particles[i].position, r)){
            found_particles.push_back(frame.all_particles[i]);
        }
    }
    if (frame.divided) {
        query(r, *frame.topLeft, found_particles);
        query(r, *frame.topRight, found_particles);
        query(r, *frame.bottomLeft, found_particles);
        query(r, *frame.bottomRight, found_particles);
    }
}

void clear_frame(Frame& frame){
    if (frame.divided) {
        std::cout<<"divided"<<std::endl;
        clear_frame(*frame.topLeft);
        clear_frame(*frame.topRight);
        clear_frame(*frame.bottomLeft);
        clear_frame(*frame.bottomRight);
    }
    std::cout<<"blah"<<std::endl;
    frame.all_particles = std::vector<Particle>();
    std::cout<<"blah"<<std::endl;
    std::cout<<frame.number_of_particles<<", "<<frame.max_number_of_particles<<std::endl;
    delete &frame;

    std::cout<<"blah"<<std::endl;
}
