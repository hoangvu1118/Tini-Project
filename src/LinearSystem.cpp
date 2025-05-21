#include "LinearSystem.h"
#include <cmath>
#include <iostream>
using namespace std;

// Constructor
LinearSystem::LinearSystem(Matrix* A, Vector* b) {
    if (A == nullptr || b == nullptr) {
        throw invalid_argument("Matrix and Vector cannot be null");
    }
    
    if (A->numRows() != A->numCols()) {
        throw invalid_argument("Matrix is not square");
    }
    
    if (A->numRows() != b->size()) {
        throw invalid_argument("Matrix and vector sizes do not match");
    }
    
    mpA = A;
    mpb = b;
    mSize = A->numRows();
}

// Destructor
LinearSystem::~LinearSystem() {}

Vector LinearSystem::Solve() {
    int n = mSize;
    Matrix augmented(n, n + 1);

    // Fill the augmented matrix [A|b]
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            augmented(i, j) = (*mpA)(i, j);
        }
        augmented(i, n + 1) = (*mpb)(i);
    }

    // Gaussian elimination
    for (int i = 1; i <= n; ++i) {
        // Pivoting
        for (int k = i + 1; k <= n; ++k) {
            if (augmented(k, i) > augmented(i, i)) {
                for (int j = 1; j <= n + 1; ++j) {
                    swap(augmented(i, j), augmented(k, j));
                }
            }
        }

        // Elimination
        for (int k = i + 1; k <= n; ++k) {
            double factor = augmented(k, i) / augmented(i, i);
            for (int j = i; j <= n + 1; ++j) {
                augmented(k, j) -= factor * augmented(i, j);
            }
        }
    }

    // Back substitution
    Vector solution(n);
    for (int i = n; i >= 1; --i) {
        double sum = 0;
        for (int j = i + 1; j <= n; ++j) {
            sum += augmented(i, j) * solution(j);
        }
        solution(i) = (augmented(i, n + 1) - sum) / augmented(i, i);
    }

    return solution;
}

// Accessor methods
int LinearSystem::Size() const { return mSize; }
Matrix* LinearSystem::GetMatrix() const { return mpA; }
Vector* LinearSystem::GetVector() const { return mpb; }
