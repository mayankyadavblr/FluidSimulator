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