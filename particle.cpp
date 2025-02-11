#include <cmath>
#include "particle.h"

bool detect_collision(Particle& p1, Particle& p2) {
    float distance = pow(pow(p1.position.x - p2.position.x, 2) + pow(p1.position.y - p2.position.y, 2), 0.5);
    if (distance <= 2*p1.radius) {
        return true;
    }
    return false;
}

void resolve_intersection(Particle& p1, Particle& p2) {
    float distance = pow(pow(p1.position.x - p2.position.x, 2) + pow(p1.position.y - p2.position.y, 2), 0.5);
    Vector line_of_contact = p1.position - p2.position;
    if (distance < 2*p1.radius) {
        p1.position = p1.position - line_of_contact * (distance / 2);
        p2.position = p2.position + line_of_contact * (distance / 2);
    }
}

void resolve_collision(Particle& p1, Particle& p2, float e = 1) {
    /*
    Incorporate coefficient of restitution
    */
    Vector line_of_contact = p1.position = p2.position;
    p1.velocity = p1.velocity - projection(p1.velocity, line_of_contact) * 2;
    p2.velocity = p2.velocity + projection(p2.velocity, line_of_contact) * 2;

}