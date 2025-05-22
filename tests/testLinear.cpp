#include <iostream>
#include <cassert>
#include <cmath>
#include "LinearSystem.h"
#include "Matrix.h"
#include "Vector.h"

using namespace std;

// Helper function to check if two doubles are approximately equal
bool isEqual(double a, double b, double epsilon = 1e-6) {
    return fabs(a - b) < epsilon;
}

void printMatrix(const Matrix& m, const string& label) {
    cout << label << ":" << endl;
    for (int i = 1; i <= m.numRows(); i++) {
        for (int j = 1; j <= m.numCols(); j++) {
            cout << const_cast<Matrix&>(m)(i, j) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void printVector(const Vector& v, const string& label) {
    cout << label << ": [";
    for (int i = 1; i <= v.size(); i++) {
        cout << const_cast<Vector&>(v)(i);
        if (i < v.size()) cout << ", ";
    }
    cout << "]" << endl;
}

void solveAndDebug2x2() {
    cout << "\n=== 2x2 System Test with Debug ===\n" << endl;
    
    // Create a simple system:
    // 2x + y = 5
    // x + 3y = 10
    // Solution: x=1, y=3
    
    Matrix* A = new Matrix(2, 2);
    (*A)(1, 1) = 2.0; (*A)(1, 2) = 1.0;
    (*A)(2, 1) = 1.0; (*A)(2, 2) = 3.0;
    
    Vector* b = new Vector(2);
    (*b)(1) = 5.0;
    (*b)(2) = 10.0;
    
    printMatrix(*A, "Coefficient Matrix A");
    printVector(*b, "Right-hand side b");
    
    LinearSystem system(A, b);
    
    cout << "Solving system..." << endl;
    Vector solution = system.Solve();
    
    printVector(solution, "Solution x");
    cout << "Expected: [1.0, 3.0]" << endl;
    
    // Verify solution
    Vector Ax(2);
    Ax(1) = (*A)(1,1) * solution(1) + (*A)(1,2) * solution(2);
    Ax(2) = (*A)(2,1) * solution(1) + (*A)(2,2) * solution(2);
    
    printVector(Ax, "A*x");
    printVector(*b, "b");
    
    cout << "Check equations:" << endl;
    cout << "2*" << solution(1) << " + " << solution(2) << " = " << Ax(1) << " (should be 5)" << endl;
    cout << solution(1) << " + 3*" << solution(2) << " = " << Ax(2) << " (should be 10)" << endl;
    
    if (isEqual(Ax(1), (*b)(1)) && isEqual(Ax(2), (*b)(2))) {
        cout << "Solution VERIFIED!" << endl;
    } else {
        cout << "ERROR: Solution does not satisfy the system!" << endl;
    }
}

void solveAndDebug3x3() {
    cout << "\n=== 3x3 System Test with Debug ===\n" << endl;
    
    // Create the system:
    // 3x + 2y + z = 10
    // 2x + 5y + 3z = 15
    // x + y + 2z = 8
    // Solution: x=1, y=1, z=3
    
    Matrix* A = new Matrix(3, 3);
    (*A)(1, 1) = 3.0; (*A)(1, 2) = 2.0; (*A)(1, 3) = 1.0;
    (*A)(2, 1) = 2.0; (*A)(2, 2) = 5.0; (*A)(2, 3) = 3.0;
    (*A)(3, 1) = 1.0; (*A)(3, 2) = 1.0; (*A)(3, 3) = 2.0;
    
    Vector* b = new Vector(3);
    (*b)(1) = 10.0;
    (*b)(2) = 15.0;
    (*b)(3) = 8.0;
    
    printMatrix(*A, "Coefficient Matrix A");
    printVector(*b, "Right-hand side b");
    
    LinearSystem system(A, b);
    
    cout << "Solving system..." << endl;
    Vector solution = system.Solve();
    
    printVector(solution, "Solution x");
    cout << "Expected: [1.0, 1.0, 3.0]" << endl;
    cout << "Differences: [" << fabs(solution(1) - 1.0) << ", " 
         << fabs(solution(2) - 1.0) << ", " 
         << fabs(solution(3) - 3.0) << "]" << endl;
    
    // Verify solution
    Vector Ax(3);
    Ax(1) = (*A)(1,1) * solution(1) + (*A)(1,2) * solution(2) + (*A)(1,3) * solution(3);
    Ax(2) = (*A)(2,1) * solution(1) + (*A)(2,2) * solution(2) + (*A)(2,3) * solution(3);
    Ax(3) = (*A)(3,1) * solution(1) + (*A)(3,2) * solution(2) + (*A)(3,3) * solution(3);
    
    printVector(Ax, "A*x");
    printVector(*b, "b");
    
    cout << "Check equations:" << endl;
    cout << "3*" << solution(1) << " + 2*" << solution(2) << " + " << solution(3) << " = " << Ax(1) << " (should be 10)" << endl;
    cout << "2*" << solution(1) << " + 5*" << solution(2) << " + 3*" << solution(3) << " = " << Ax(2) << " (should be 15)" << endl;
    cout << solution(1) << " + " << solution(2) << " + 2*" << solution(3) << " = " << Ax(3) << " (should be 8)" << endl;
    
    if (isEqual(Ax(1), (*b)(1)) && isEqual(Ax(2), (*b)(2)) && isEqual(Ax(3), (*b)(3))) {
        cout << "Solution VERIFIED!" << endl;
    } else {
        cout << "ERROR: Solution does not satisfy the system!" << endl;
    }
}

void tryDirectSolution3x3() {
    cout << "\n=== Manual Solution Attempt ===\n" << endl;
    
    // Create a fresh system
    Matrix A(3, 3);
    A(1, 1) = 3.0; A(1, 2) = 2.0; A(1, 3) = 1.0;
    A(2, 1) = 2.0; A(2, 2) = 5.0; A(2, 3) = 3.0;
    A(3, 1) = 1.0; A(3, 2) = 1.0; A(3, 3) = 2.0;
    
    Vector b(3);
    b(1) = 10.0;
    b(2) = 15.0;
    b(3) = 8.0;
    
    // Create an augmented matrix [A|b]
    Matrix aug(3, 4);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            aug(i, j) = A(i, j);
        }
        aug(i, 4) = b(i);
    }
    
    printMatrix(aug, "Augmented Matrix [A|b]");
    
    // Forward elimination with pivoting
    for (int i = 1; i <= 3; i++) {
        // Find pivot row
        int maxRow = i;
        for (int k = i + 1; k <= 3; k++) {
            if (fabs(aug(k, i)) > fabs(aug(maxRow, i))) {
                maxRow = k;
            }
        }
        
        cout << "Pivot position (" << i << "," << i << "), value = " << aug(maxRow, i) << endl;
        
        // Swap rows if necessary
        if (maxRow != i) {
            cout << "Swapping rows " << i << " and " << maxRow << endl;
            for (int j = 1; j <= 4; j++) {
                double temp = aug(i, j);
                aug(i, j) = aug(maxRow, j);
                aug(maxRow, j) = temp;
            }
        }
        
        printMatrix(aug, "After row swap");
        
        // Elimination step
        for (int k = i + 1; k <= 3; k++) {
            double factor = aug(k, i) / aug(i, i);
            cout << "Eliminating below position (" << i << "," << i << "), factor = " << factor << endl;
            
            for (int j = i; j <= 4; j++) {
                aug(k, j) -= factor * aug(i, j);
            }
        }
        
        printMatrix(aug, "After elimination");
    }
    
    // Back substitution
    Vector x(3);
    for (int i = 3; i >= 1; i--) {
        double sum = 0.0;
        for (int j = i + 1; j <= 3; j++) {
            sum += aug(i, j) * x(j);
        }
        x(i) = (aug(i, 4) - sum) / aug(i, i);
        cout << "Set x(" << i << ") = (" << aug(i, 4) << " - " << sum << ") / " << aug(i, i) << " = " << x(i) << endl;
    }
    
    printVector(x, "Manual solution");
    
    // Verify solution
    Vector Ax(3);
    for (int i = 1; i <= 3; i++) {
        double sum = 0.0;
        for (int j = 1; j <= 3; j++) {
            sum += A(i, j) * x(j);
        }
        Ax(i) = sum;
    }
    
    printVector(Ax, "A*x (manual solution)");
    printVector(b, "b");
    
    if (isEqual(Ax(1), b(1)) && isEqual(Ax(2), b(2)) && isEqual(Ax(3), b(3))) {
        cout << "Manual solution VERIFIED!" << endl;
    } else {
        cout << "ERROR: Manual solution does not satisfy the system!" << endl;
    }
}

int main() {
    cout << "=== SIMPLE LINEAR SYSTEM TEST ===\n" << endl;
    
    solveAndDebug2x2();
    solveAndDebug3x3();
    tryDirectSolution3x3();
    
    return 0;
}
