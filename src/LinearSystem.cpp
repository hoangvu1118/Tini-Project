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

    // Print the initial augmented matrix for debugging
    cout << "Initial augmented matrix:" << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n+1; ++j) {
            cout << augmented(i, j) << " ";
        }
        cout << endl;
    }

    // Forward elimination
    for (int i = 1; i <= n; ++i) {
        // Find pivot with largest absolute value
        int maxRow = i;
        for (int k = i + 1; k <= n; ++k) {
            if (fabs(augmented(k, i)) > fabs(augmented(maxRow, i))) {
                maxRow = k;
            }
        }
        
        // Swap rows if needed
        if (maxRow != i) {
            for (int j = 1; j <= n + 1; ++j) {
                double temp = augmented(i, j);
                augmented(i, j) = augmented(maxRow, j);
                augmented(maxRow, j) = temp;
            }
        }
        
        // Check for singular matrix
        if (fabs(augmented(i, i)) < 1e-10) {
            throw runtime_error("Matrix is singular or nearly singular");
        }

        // Elimination
        for (int k = i + 1; k <= n; ++k) {
            double factor = augmented(k, i) / augmented(i, i);
            for (int j = i; j <= n + 1; ++j) {
                augmented(k, j) -= factor * augmented(i, j);
            }
        }
    }

    // Print the matrix after elimination for debugging
    cout << "Matrix after elimination:" << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n+1; ++j) {
            cout << augmented(i, j) << " ";
        }
        cout << endl;
    }

    // Back substitution
    Vector solution(n);
    for (int i = n; i >= 1; --i) {
        double sum = 0.0;
        for (int j = i + 1; j <= n; ++j) {
            sum += augmented(i, j) * solution(j);
        }
        solution(i) = (augmented(i, n + 1) - sum) / augmented(i, i);
        
        // Print each step of back substitution for debugging
        cout << "Set solution(" << i << ") = (" << augmented(i, n + 1) 
             << " - " << sum << ") / " << augmented(i, i) 
             << " = " << solution(i) << endl;
    }

    // Print final solution for debugging
    cout << "Final solution: ";
    for (int i = 1; i <= n; ++i) {
        cout << solution(i) << " ";
    }
    cout << endl;

    return solution;
}

// Accessor methods
int LinearSystem::Size() const { return mSize; }
Matrix* LinearSystem::GetMatrix() const { return mpA; }
Vector* LinearSystem::GetVector() const { return mpb; }
