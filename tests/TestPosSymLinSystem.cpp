#include <iostream>
#include <cmath>
#include <iomanip>
#include <LinearSystem.h>
#include <PosSymLinSystem.h>
#include <Matrix.h>
#include <Vector.h>
using namespace std;

// Helper function to print vector
void printVector(Vector& v, const string& label) {
    cout << label << " = [";
    for (int i = 1; i <= v.size(); ++i) {
        cout << fixed << setprecision(6) << v(i);
        if (i < v.size()) cout << ", ";
    }
    cout << "]" << endl;
}

// Helper function to print matrix
void printMatrix(const Matrix& A, const string& label) {
    cout << label << " = " << endl;
    for (int i = 1; i <= A.numRows(); ++i) {
        cout << "[";
        for (int j = 1; j <= A.numCols(); ++j) {
            cout << fixed << setprecision(4) << A(i, j);
            if (j < A.numCols()) cout << ", ";
        }
        cout << "]" << endl;
    }
}

// Create a symmetric positive definite matrix
void createSPDMatrix(Matrix& A, int n) {
    // First create a random matrix
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            A(i, j) = rand() % 10 + 1;  // Random values between 1 and 10
        }
    }
    
    // Make it symmetric
    for (int i = 1; i <= n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            A(j, i) = A(i, j);
        }
    }
    
    // Make it diagonally dominant (sufficient condition for positive definiteness)
    for (int i = 1; i <= n; ++i) {
        double rowSum = 0;
        for (int j = 1; j <= n; ++j) {
            if (i != j) rowSum += fabs(A(i, j));
        }
        A(i, i) = rowSum + rand() % 10 + 1;  // Ensure diagonal > sum of other elements
    }
}

int main() {
    try {
        cout << "===== Testing PosSymLinSystem with Conjugate Gradient Method =====" << endl << endl;
        
        // Test case 1: 2x2 system
        cout << "Test Case 1: 2x2 System" << endl;
        Matrix A1(2, 2);
        A1(1, 1) = 4; A1(1, 2) = 1;
        A1(2, 1) = 1; A1(2, 2) = 3;  // Symmetric positive definite
        
        Vector b1(2);
        b1(1) = 1; b1(2) = 2;
        
        printMatrix(A1, "Matrix A");
        printVector(b1, "Vector b");
        
        PosSymLinSystem system1(&A1, &b1);
        Vector solution1 = system1.Solve();
        
        // Compute residual to verify solution
        Vector residual1 = b1 - A1 * solution1;
        printVector(solution1, "Solution x");
        printVector(residual1, "Residual (b-Ax)");
        cout << "Residual norm: " << sqrt(residual1.dot(residual1)) << endl << endl;
        
        // Test case 2: 3x3 system
        cout << "Test Case 2: 3x3 System" << endl;
        Matrix A2(3, 3);
        A2(1, 1) = 4; A2(1, 2) = 1; A2(1, 3) = 0;
        A2(2, 1) = 1; A2(2, 2) = 3; A2(2, 3) = 1;
        A2(3, 1) = 0; A2(3, 2) = 1; A2(3, 3) = 2;
        
        Vector b2(3);
        b2(1) = 5; b2(2) = 5; b2(3) = 3;
        
        printMatrix(A2, "Matrix A");
        printVector(b2, "Vector b");
        
        PosSymLinSystem system2(&A2, &b2);
        Vector solution2 = system2.Solve();
        
        // Compute residual
        Vector residual2 = b2 - A2 * solution2;
        printVector(solution2, "Solution x");
        printVector(residual2, "Residual (b-Ax)");
        cout << "Residual norm: " << sqrt(residual2.dot(residual2)) << endl << endl;
        
        // Test case 3: Larger random SPD system
        cout << "Test Case 3: 5x5 Random SPD System" << endl;
        int n = 5;
        Matrix A3(n, n);
        createSPDMatrix(A3, n);
        
        Vector b3(n);
        for (int i = 1; i <= n; ++i) {
            b3(i) = rand() % 20 - 10;  // Random values between -10 and 10
        }
        
        printMatrix(A3, "Matrix A");
        printVector(b3, "Vector b");
        
        PosSymLinSystem system3(&A3, &b3);
        Vector solution3 = system3.Solve();
        
        // Compute residual
        Vector residual3 = b3 - A3 * solution3;
        printVector(solution3, "Solution x");
        printVector(residual3, "Residual (b-Ax)");
        cout << "Residual norm: " << sqrt(residual3.dot(residual3)) << endl << endl;
        
        // Test case 4: Error handling - non-symmetric matrix
        cout << "Test Case 4: Non-symmetric Matrix Error Handling" << endl;
        Matrix A4(2, 2);
        A4(1, 1) = 4; A4(1, 2) = 1;
        A4(2, 1) = 2; A4(2, 2) = 3;  // Not symmetric
        
        Vector b4(2);
        b4(1) = 1; b4(2) = 2;
        
        try {
            PosSymLinSystem system4(&A4, &b4);
            cout << "ERROR: Should have thrown exception for non-symmetric matrix" << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Correctly caught exception: " << e.what() << endl << endl;
        }
        
    } catch (const exception& e) {
        cerr << "Unexpected exception: " << e.what() << endl;
        return 1;
    }
    
    cout << "All tests completed." << endl;
    return 0;
}