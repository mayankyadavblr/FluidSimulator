#include "frame.h"

int main(){
    Frame frame;
    frame.dt = 1/60;
    frame.number_of_particles = 1;
    
    Particle p;
    frame.all_particles.push_back(p);

    update_frame(frame);

    return 0;
}