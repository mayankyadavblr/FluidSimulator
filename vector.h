#ifndef VECTOR_H 
#define VECTOR_H

struct Vector {
    float x;
    float y;    
    
};

inline Vector operator +(Vector lhs, Vector rhs);

inline Vector operator -(Vector lhs, Vector rhs);

inline Vector operator *(Vector lhs, Vector rhs);

inline Vector operator /(Vector lhs, Vector rhs);

inline bool operator ==(Vector lhs, Vector rhs);

Vector dot(Vector lhs, Vector rhs);

inline Vector operator *(Vector lhs, float rhs);

#endif 