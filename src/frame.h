#ifndef FRAME_H 
#define FRAME_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "particle.h"

struct Rectangle {
    Vector center;
    double width;
    double height;
};
struct Frame {
    double dt = 1.00/60.00; // Set to inverse of desired frame rate
    int number_of_particles=0;
    int max_number_of_particles = 10;
    std::vector<Particle*> all_particles;

    Rectangle boundary;
    Vector tr, bl; 

    bool divided = false;

    Frame* topLeft;
    Frame* topRight;
    Frame* bottomLeft;
    Frame* bottomRight;
};

void update_particle(Particle* p, double dt);

Particle inverse_update_particle(Particle p, double dt);

void update_frame(Frame& frame);

void check_boundaries(Frame& frame, Vector tr, Vector bl);

void subdivide_frame(Frame& frame);

void insert_point(Particle* p, Frame& frame);

bool contains(Vector p, Rectangle boundary);

bool intersects(Rectangle r1, Rectangle r2);

void query(Rectangle r, Frame& frame, std::vector<Particle*>& found_particles);

void clear_frame(Frame* frame);

void clear_quad_tree(Frame& quad_tree);

void show_details(Frame frame);

void draw_quad_tree(sf::RenderWindow& window, Frame frame);

#endif 