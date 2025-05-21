#pragma once

#include <iostream>
using namespace std;

class Vector {
private:
    int mSize;
    double* mData;

public:
    // Constructor
    Vector(int size) : mSize(size) {}

    // Copy Constructor
    Vector(const Vector& other) : mSize(other.mSize) {}

    // Destructor
    ~Vector() {}

    // Assignment Operator
    Vector& operator=(const Vector& other) {}

    // Unary Operator Overload
    Vector operator-() const {}

    // Binary Operator Overloads
    Vector operator+(const Vector& other) const {}

    Vector operator-(const Vector& other) const {}

    Vector operator*(double scalar) const {}
    
    // Square Bracket Operator Overload for index checking
    double& operator[](int index) {}

    // Round Bracket Operator Overload for one-based indexing
    double& operator()(int index) {}
    

    // Get size of the vector
    int size() const {}
};
