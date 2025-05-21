# pragma once

#include "Matrix.h"
#include "Vector.h"
using namespace std;

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
    int Size() const {}
    Matrix* GetMatrix() const {}
    Vector* GetVector() const {}
    void SwapRows(Matrix& A, Ve) {}

private:
    // Disabled copy constructor and assignment operator
    LinearSystem (const LinearSystem&);
    LinearSystem& operator=(const LinearSystem&);
};
