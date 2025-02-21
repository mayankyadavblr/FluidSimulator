#include "frame.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int temp(){
    Frame frame;
    frame.dt = 1.00/60.00;
    frame.number_of_particles = 1;
    
    Particle p1;
    p1.position = Vector{0, 0};
    p1.velocity = Vector{0, -10};

    Particle p2;
    p2.position = Vector{0, 5};
    p2.velocity = Vector{0, 10};
    
    frame.all_particles.push_back(p1);
    frame.all_particles.push_back(p2);
    frame.number_of_particles = 2;

    update_frame(frame);

    display_details(frame.all_particles[0]);
    display_details(frame.all_particles[1]);

    return 0;
}