#include <PosSymLinSystem.h>
#include <Matrix.h>
#include <Vector.h>
#include <math.h>
#include <iostream>

using namespace std;

// Constructor
PosSymLinSystem::PosSymLinSystem(Matrix* A, Vector* b) : LinearSystem(A, b) {
    if (!isSymmetric(*A)) {
        throw invalid_argument("Matrix is not symmetric");
    }
}

// Destructor
PosSymLinSystem::~PosSymLinSystem() {}

// Check if the matrix is symmetric
bool PosSymLinSystem::isSymmetric(const Matrix& A) {
    int n = A.numRows();
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (fabs(A(i, j) - A(j, i)) > 1e-10) {
                return false;
            }
        }
    }
    return true;
}

// Solve method
Vector PosSymLinSystem::Solve() {
    int n = mSize;
    Vector x(n);
    Vector r(n);
    r = *mpb;
    Vector p(n);
    p = r;
    
    // Store r dot r for convergence check
    double rsold = r.dot(r);
    
    // Convergence parameters
    const double tolerance = 1e-10;
    const int maxIterations = n * 2;
    
    cout << "Starting Conjugate Gradient method..." << endl;
    
    for (int iter = 0; iter < maxIterations; ++iter) {
        // Matrix-vector product A*p
        Vector Ap(n);
        // Manually perform the matrix-vector multiplication
        for (int i = 1; i <= n; ++i) {
            double sum = 0.0;
            for (int j = 1; j <= n; ++j) {
                sum += (*mpA)(i, j) * p(j);
            }
            Ap(i) = sum;
        }
        
        double alpha = rsold / p.dot(Ap);
        
        x = x + p * alpha;
        r = r - Ap * alpha;
        
        double rsnew = r.dot(r);
        
        double error = sqrt(rsnew);
        cout << "Iteration " << iter + 1 << ", Error = " << error << endl;
        
        if (error < tolerance) {
            cout << "Conjugate Gradient converged after " << iter + 1 << " iterations" << endl;
            break;
        }
        
        double beta = rsnew / rsold;
        p = r + p * beta;
        rsold = rsnew;
        
        if (iter == maxIterations - 1) {
            cout << "Warning: Conjugate Gradient did not converge within " 
                 << maxIterations << " iterations" << endl;
        }
    }
    
    cout << "Final solution: ";
    for (int i = 1; i <= n; ++i) {
        cout << x(i) << " ";
    }
    cout << endl;
    
    return x;
}

