#include <iostream>
#include <LinearSystem.h>
#include <Vector.h>
#include <Matrix.h>
#include <cmath>

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

Vector matrixVectorMultiply( Matrix& A, Vector& x) {
    int m = A.numRows();
    int n = A.numCols();
    Vector result(m);
    
    for (int i = 1; i <= m; i++) {
        double sum = 0.0;
        for (int j = 1; j <= n; j++) {
            sum += A(i, j) * x(j);
        }
        result(i) = sum;
    }
    return result;
}

void printVector( Vector& v, const std::string& name) {
    std::cout << name << " = [";
    for (int i = 1; i <= v.size(); i++) {
        std::cout << v(i);
        if (i < v.size()) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

double vectorNorm( Vector& v) {
    double sum = 0.0;
    for (int i = 1; i <= v.size(); i++) {
        sum += v(i) * v(i);
    }
    return std::sqrt(sum);
}
void testPseudoinverse(Matrix& A, Vector& b, const std::string& description) {
    std::cout << "\n" << description << std::endl;
    std::cout << "Matrix A (" << A.numRows() << "x" << A.numCols() << "):" << std::endl;
    
    for (int i = 1; i <= A.numRows(); i++) {
        for (int j = 1; j <= A.numCols(); j++) {
            std::cout << A(i, j) << "\t";
        }
        std::cout << std::endl;
    }
    
    printVector(b, "Vector b");
    
    // Solve using pseudoinverse
    Matrix A_copy = A; // Create copy since solvePseudoinverse takes non-const reference
    Vector b_copy = b;
    Vector x = solvePseudoinverse(A_copy, b_copy);
    printVector(x, "Solution x");
    
    // Verify solution
    Vector Ax = matrixVectorMultiply(A, x);
    printVector(Ax, "Verification A*x");
    
    // Calculate and display metrics
    Vector residual(b.size());
    for (int i = 1; i <= b.size(); i++) {
        residual(i) = Ax(i) - b(i);
    }
    
    double residual_norm = vectorNorm(residual);
    double solution_norm = vectorNorm(x);
    
    std::cout << "Residual norm ||Ax - b|| = " << residual_norm << std::endl;
    std::cout << "Solution norm ||x|| = " << solution_norm << std::endl;
}

void solveMoorePenrose() {
    std::cout << "===== Moore-Penrose Pseudoinverse Solutions =====" << std::endl;

    // Example 1: Underdetermined system
    Matrix A1(3, 5);
    A1(1, 1) = 1.0; A1(1, 2) = 2.0; A1(1, 3) = 3.0; A1(1, 4) = 4.0; A1(1, 5) = 5.0;
    A1(2, 1) = 0.1; A1(2, 2) = 0.4; A1(2, 3) = 0.9; A1(2, 4) = 1.6; A1(2, 5) = 2.5;
    A1(3, 1) = 2.0; A1(3, 2) = 1.0; A1(3, 3) = 1.0; A1(3, 4) = 2.0; A1(3, 5) = 3.0;

    Vector b1(3);
    b1(1) = 15.0; b1(2) = 5.5; b1(3) = 9.0;

    testPseudoinverse(A1, b1, "Example 1: Underdetermined system (3 equations, 5 unknowns)");

    // Example 2: Overdetermined system
    Matrix A2(5, 3);
    A2(1, 1) = 1.0; A2(1, 2) = 0.0; A2(1, 3) = 0.0;
    A2(2, 1) = 1.0; A2(2, 2) = 1.0; A2(2, 3) = 0.0;
    A2(3, 1) = 1.0; A2(3, 2) = 0.0; A2(3, 3) = 1.0;
    A2(4, 1) = 1.0; A2(4, 2) = 1.0; A2(4, 3) = 1.0;
    A2(5, 1) = 0.0; A2(5, 2) = 0.0; A2(5, 3) = 1.0;

    Vector b2(5);
    b2(1) = 1.1; b2(2) = 2.2; b2(3) = 1.9; b2(4) = 4.0; b2(5) = 1.1;

    testPseudoinverse(A2, b2, "Example 2: Overdetermined system (5 equations, 3 unknowns)");
}

int main() {
    std::cout << "Solving Ill-Posed Linear Systems with Moore-Penrose Pseudoinverse" << std::endl;
    std::cout << "=========================================================" << std::endl;
    
    try {
        solveMoorePenrose();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}