#include "vector.h"


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

Vector dot(Vector lhs, Vector rhs) {
    return Vector{lhs.x * rhs.x, lhs.y * rhs.y};
}