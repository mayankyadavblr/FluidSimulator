#ifndef VECTOR_H 
#define VECTOR_H

struct Vector {
    float x;
    float y;    
    
};

inline Vector operator +(Vector lhs, Vector rhs);

inline Vector operator -(Vector lhs, Vector rhs);

inline Vector operator *(Vector lhs, Vector rhs);

inline Vector operator *(Vector lhs, float rhs);

inline Vector operator /(Vector lhs, Vector rhs);

inline bool operator ==(Vector lhs, Vector rhs);

float dot(Vector lhs, Vector rhs);

float magnitude(Vector v);

float angle_between_vectors(Vector v1, Vector v2);

Vector projection(Vector v1, Vector v2);

float distance(Vector v1, Vector v2);

#endif 