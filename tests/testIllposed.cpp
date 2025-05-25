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

void solveMoorePenrose()
{
    std::cout << "===== Moore-Penrose Pseudoinverse Solutions =====" << std::endl;

    // Example 1: Underdetermined system (more unknowns than equations)
    std::cout << "\nExample 1: Underdetermined system (3 equations, 5 unknowns)" << std::endl;
    int m1 = 3; // Number of equations
    int n1 = 5; // Number of unknowns

    Matrix A1(m1, n1);
    // Fill A with values
    A1(1, 1) = 1.0;
    A1(1, 2) = 2.0;
    A1(1, 3) = 3.0;
    A1(1, 4) = 4.0;
    A1(1, 5) = 5.0;
    A1(2, 1) = 0.1;
    A1(2, 2) = 0.4;
    A1(2, 3) = 0.9;
    A1(2, 4) = 1.6;
    A1(2, 5) = 2.5;
    A1(3, 1) = 2.0;
    A1(3, 2) = 1.0;
    A1(3, 3) = 1.0;
    A1(3, 4) = 2.0;
    A1(3, 5) = 3.0;

    Vector b1(m1);
    b1(1) = 15.0;
    b1(2) = 5.5;
    b1(3) = 9.0;

    std::cout << "Matrix A:" << std::endl;
    for (int i = 1; i <= m1; i++)
    {
        for (int j = 1; j <= n1; j++)
        {
            std::cout << A1(i, j) << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "Vector b: [";
    for (int i = 1; i <= m1; i++)
    {
        std::cout << b1(i);
        if (i < m1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // Solve using pseudoinverse
    Vector x1 = solvePseudoinverse(A1, b1);
    std::cout << "Solution using Pseudoinverse:" << std::endl;
    std::cout << "x = [";
    for (int i = 1; i <= n1; i++)
    {
        std::cout << x1(i);
        if (i < n1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // Verify pseudoinverse solution
    Vector Ax1(m1);
    for (int i = 1; i <= m1; i++)
    {
        double sum = 0.0;
        for (int j = 1; j <= n1; j++)
        {
            sum += A1(i, j) * x1(j);
        }
        Ax1(i) = sum;
    }

    std::cout << "Verification A*x = [";
    for (int i = 1; i <= m1; i++)
    {
        std::cout << Ax1(i);
        if (i < m1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    std::cout << "Original b = [";
    for (int i = 1; i <= m1; i++)
    {
        std::cout << b1(i);
        if (i < m1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // Calculate residual norm ||Ax - b||
    double residual1 = 0.0;
    for (int i = 1; i <= m1; i++)
    {
        residual1 += pow(Ax1(i) - b1(i), 2);
    }
    residual1 = sqrt(residual1);
    std::cout << "Residual norm ||Ax - b|| = " << residual1 << std::endl;

    // Calculate solution norm ||x||
    double sol_norm1 = 0.0;
    for (int i = 1; i <= n1; i++)
    {
        sol_norm1 += pow(x1(i), 2);
    }
    sol_norm1 = sqrt(sol_norm1);
    std::cout << "Solution norm ||x|| = " << sol_norm1 << std::endl;

    // Example 2: Overdetermined system (more equations than unknowns)
    std::cout << "\nExample 2: Overdetermined system (5 equations, 3 unknowns)" << std::endl;
    int m2 = 5; // Number of equations
    int n2 = 3; // Number of unknowns

    Matrix A2(m2, n2);
    // Fill A with values for a least squares problem
    A2(1, 1) = 1.0;
    A2(1, 2) = 0.0;
    A2(1, 3) = 0.0;
    A2(2, 1) = 1.0;
    A2(2, 2) = 1.0;
    A2(2, 3) = 0.0;
    A2(3, 1) = 1.0;
    A2(3, 2) = 0.0;
    A2(3, 3) = 1.0;
    A2(4, 1) = 1.0;
    A2(4, 2) = 1.0;
    A2(4, 3) = 1.0;
    A2(5, 1) = 0.0;
    A2(5, 2) = 0.0;
    A2(5, 3) = 1.0;

    Vector b2(m2);
    b2(1) = 1.1; // Adding some noise to make it inconsistent
    b2(2) = 2.2;
    b2(3) = 1.9;
    b2(4) = 4.0;
    b2(5) = 1.1;

    std::cout << "Matrix A:" << std::endl;
    for (int i = 1; i <= m2; i++)
    {
        for (int j = 1; j <= n2; j++)
        {
            std::cout << A2(i, j) << "\t";
        }
        std::cout << std::endl;
    }

    std::cout << "Vector b: [";
    for (int i = 1; i <= m2; i++)
    {
        std::cout << b2(i);
        if (i < m2)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // Solve using pseudoinverse
    Vector x2 = solvePseudoinverse(A2, b2);
    std::cout << "Solution using Pseudoinverse:" << std::endl;
    std::cout << "x = [";
    for (int i = 1; i <= n2; i++)
    {
        std::cout << x2(i);
        if (i < n2)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // Verify pseudoinverse solution
    Vector Ax2(m2);
    for (int i = 1; i <= m2; i++)
    {
        double sum = 0.0;
        for (int j = 1; j <= n2; j++)
        {
            sum += A2(i, j) * x2(j);
        }
        Ax2(i) = sum;
    }

    std::cout << "Verification A*x = [";
    for (int i = 1; i <= m2; i++)
    {
        std::cout << Ax2(i);
        if (i < m2)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    std::cout << "Original b = [";
    for (int i = 1; i <= m2; i++)
    {
        std::cout << b2(i);
        if (i < m2)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    // Calculate residual norm ||Ax - b||
    double residual2 = 0.0;
    for (int i = 1; i <= m2; i++)
    {
        residual2 += pow(Ax2(i) - b2(i), 2);
    }
    residual2 = sqrt(residual2);
    std::cout << "Residual norm ||Ax - b|| = " << residual2 << std::endl;
}

int main() {
    std::cout << "Solving Ill-Posed Linear Systems with Moore-Penrose Pseudoinverse" << std::endl;
    std::cout << "=========================================================" << std::endl;
    
    try {
        solveMoorePenrose();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}
