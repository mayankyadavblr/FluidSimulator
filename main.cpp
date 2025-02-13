#include "frame.h"
#include <iostream>

int main(){
    Frame frame;
    frame.dt = 1.00/60.00;
    frame.number_of_particles = 1;
    
    Particle p;
    p.velocity = Vector{5, 0};
    frame.all_particles.push_back(p);

    update_frame(frame);
    std::cout << "particle position: " << frame.all_particles[0].position.x <<","<< frame.all_particles[0].position.y<<std::endl;
    return 0;
}