#include "vector.h"
#include <cmath>

Vector operator +(Vector lhs, Vector rhs) {
    return Vector{lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector operator -(Vector lhs, Vector rhs) {
    return Vector{lhs.x - rhs.x, lhs.y - rhs.y};
}

Vector operator *(Vector lhs, double rhs) {
    return Vector{lhs.x * rhs, lhs.y * rhs};
}

Vector operator /(Vector lhs, double rhs) {
    /*
    Note: need to handle division by zero
    */
    return Vector{lhs.x / rhs, lhs.y / rhs};
}

bool operator ==(Vector lhs, Vector rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

double dot(Vector lhs, Vector rhs) {
    /*
    Dot product of two vectors
    */
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double magnitude(Vector v) {
    /*
    Magnitude of a vector
    */
    return pow(pow(v.x, 2) + pow(v.y, 2), 0.5);
}

double angle_between_vectors(Vector v1, Vector v2) {
    /*
    Angle between two vectors via the formula
    a.b = |a||b|cos(theta)

    Note: need to handle division by zero
    */
    double dot_product = dot(v1, v2);
    double mag1 = magnitude(v1);
    double mag2 = magnitude(v2);

    return acos(dot_product/(mag1 * mag2));

}

Vector projection(Vector v1, Vector v2) {
    /*
    Projection of vector v1 on vector v2
    Formula: (v1.v2/|v2|) * v1/|v1|
    Or: |v1| * cos(theta) * v2/|v2|

    Note: need to handle division by zero
    */
    double dot_product = dot(v1, v2);
    double mag2 = magnitude(v2);

    return v2 * (dot_product/pow(mag2, 2));
}

double distance(Vector v1, Vector v2) {
    /*
    Distance between two points in 2-D
    coordinate system given by their vector
    position.

    formula: classic distance formula (RMS)
    */

    return pow(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2), 0.5);
}