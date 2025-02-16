#ifndef VECTOR_H 
#define VECTOR_H

struct Vector {
    double x;
    double y;    
    
};

Vector operator +(Vector lhs, Vector rhs);

Vector operator -(Vector lhs, Vector rhs);

Vector operator *(Vector lhs, Vector rhs);

Vector operator *(Vector lhs, double rhs);

Vector operator /(Vector lhs, double rhs);

bool operator ==(Vector lhs, Vector rhs);

double dot(Vector lhs, Vector rhs);

double magnitude(Vector v);

double angle_between_vectors(Vector v1, Vector v2);

Vector projection(Vector v1, Vector v2);

double distance(Vector v1, Vector v2);

#endif 