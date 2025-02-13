#include "frame.h"
#include <iostream>

int main(){
    Frame frame;
    frame.dt = 1/60;
    frame.number_of_particles = 1;
    std::cout << "timestep: "<<frame.dt<<std::endl;
    Particle p;
    frame.all_particles.push_back(p);

    update_frame(frame);

    return 0;
}