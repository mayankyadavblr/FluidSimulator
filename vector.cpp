#include "vector.h"
#include <cmath>

inline Vector operator +(Vector lhs, Vector rhs) {
    return Vector{lhs.x + rhs.x, lhs.y + rhs.y};
}

inline Vector operator -(Vector lhs, Vector rhs) {
    return Vector{lhs.x - rhs.x, lhs.y - rhs.y};
}

inline Vector operator *(Vector lhs, Vector rhs) {
    return Vector{lhs.x * rhs.x, lhs.y * rhs.y};
}

inline Vector operator *(Vector lhs, float rhs) {
    return Vector{lhs.x * rhs, lhs.y * rhs};
}

inline Vector operator /(Vector lhs, Vector rhs) {
    return Vector{lhs.x / rhs.x, lhs.y / rhs.y};
}

inline bool operator ==(Vector lhs, Vector rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

float dot(Vector lhs, Vector rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

float magnitude(Vector v) {
    return pow(v.x, 2) + pow(v.y, 2);
}

float angle_between_vectors(Vector v1, Vector v2) {
    float dot_product = dot(v1, v2);
    float mag1 = magnitude(v1);
    float mag2 = magnitude(v2);

    return acos(dot_product/(mag1 * mag2));

}

Vector projection(Vector v1, Vector v2) {
    float dot_product = dot(v1, v2);
    float mag2 = magnitude(v2);
    float mag1 = magnitude(v1);

    return v2 * (dot_product/mag2);
}