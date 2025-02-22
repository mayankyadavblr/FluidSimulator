#ifndef FRAME_H 
#define FRAME_H
#include <vector>

#include "particle.h"

struct Rectangle {
    Vector center;
    double width;
    double height;
};
struct Frame {
    double dt; // Set to inverse of desired frame rate
    int number_of_particles;
    int max_number_of_particles;
    std::vector<Particle> all_particles;

    Rectangle boundary;
    Vector tr, bl; 

    bool divided = false;

    Frame* topLeft;
    Frame* topRight;
    Frame* bottomLeft;
    Frame* bottomRight;
};

void update_particle(Particle& p, double dt);

Particle inverse_update_particle(Particle p, double dt);

void update_frame(Frame& frame);

void check_boundaries(Frame& frame);

void subdivide_frame(Frame& frame);

void insert_point(Particle& p, Frame& frame);

bool contains(Vector p, Rectangle boundary);

bool intersects(Rectangle r1, Rectangle r2);

std::vector<Particle> query(Rectangle r, Frame& frame, std::vector<Particle>& found_particles);

#endif 