# pragma once

#include "Matrix.h"
#include "Vector.h"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

public:
    // Constructor
    LinearSystem(Matrix* A, Vector* b);

    // Destructor
    virtual ~LinearSystem();

    // Solve method to be overridden in derived classes
    virtual Vector Solve() = 0;

    // Accessor methods
    int Size() const { return mSize; }
    Matrix* GetMatrix() const { return mpA; }
    Vector* GetVector() const { return mpb; }
};
