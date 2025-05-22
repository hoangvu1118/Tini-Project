#include <iostream>
#include <LinearSystem.h>
#include <Vector.h>
#include <Matrix.h>
#include <cmath>

// Function to solve ill-posed problems using pseudoinverse
Vector solvePseudoinverse(Matrix& A, Vector& b) {

    Matrix Aplus = A.pseudoInverse();

    int m = Aplus.numRows();
    int n = b.size();
    Vector x(m);
    
    for (int i = 1; i <= m; i++) {
        double sum = 0.0;
        for (int j = 1; j <= n; j++) {
            sum += Aplus(i, j) * b(j);
        }
        x(i) = sum;
    }
    
    return x;
}

int main() {
    
    return 0;
}



