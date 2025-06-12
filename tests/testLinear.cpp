#include <iostream>
#include <cassert>
#include <cmath>
#include "LinearSystem.h"
#include "Matrix.h"
#include "Vector.h"

using namespace std;

bool isEqual(double a, double b, double epsilon = 1e-6) {
    return fabs(a - b) < epsilon;
}

void printMatrix(Matrix& m, const string& label) {
    cout << label << ":" << endl;
    for (int i = 1; i <= m.numRows(); i++) {
        for (int j = 1; j <= m.numCols(); j++) {
            cout << m(i, j) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void printVector(Vector& v, const string& label) {
    cout << label << ": [";
    for (int i = 1; i <= v.size(); i++) {
        cout << v(i);
        if (i < v.size()) cout << ", ";
    }
    cout << "]" << endl;
}

bool verifySolution(Matrix& A, Vector& x, Vector& b) {
    Vector Ax(b.size());
    for (int i = 1; i <= A.numRows(); i++) {
        double sum = 0.0;
        for (int j = 1; j <= A.numCols(); j++) {
            sum += A(i, j) * x(j);
        }
        Ax(i) = sum;
    }
    
    printVector(Ax, "A*x");
    printVector(b, "b");
    
    for (int i = 1; i <= b.size(); i++) {
        if (!isEqual(Ax(i), b(i))) return false;
    }
    return true;
}

void solveAndDebug2x2() {
    cout << "\n=== 2x2 System Test with Debug ===\n" << endl;
    
    Matrix A(2, 2);
    A(1, 1) = 2.0; A(1, 2) = 1.0;
    A(2, 1) = 1.0; A(2, 2) = 3.0;
    
    Vector b(2);
    b(1) = 5.0;
    b(2) = 10.0;
    
    printMatrix(A, "Coefficient Matrix A");
    printVector(b, "Right-hand side b");
    
    LinearSystem system(&A, &b);
    Vector solution = system.Solve();
    
    printVector(solution, "Solution x");
    cout << "Expected: [1.0, 3.0]" << endl;
    
    if (verifySolution(A, solution, b)) {
        cout << "Solution VERIFIED!" << endl;
    } else {
        cout << "ERROR: Solution does not satisfy the system!" << endl;
    }
}

void solveAndDebug3x3() {
    cout << "\n=== 3x3 System Test with Debug ===\n" << endl;
    
    Matrix A(3, 3);
    A(1, 1) = 3.0; A(1, 2) = 2.0; A(1, 3) = 1.0;
    A(2, 1) = 2.0; A(2, 2) = 5.0; A(2, 3) = 3.0;
    A(3, 1) = 1.0; A(3, 2) = 1.0; A(3, 3) = 2.0;
    
    Vector b(3);
    b(1) = 10.0;
    b(2) = 15.0;
    b(3) = 8.0;
    
    printMatrix(A, "Coefficient Matrix A");
    printVector(b, "Right-hand side b");
    
    LinearSystem system(&A, &b);
    Vector solution = system.Solve();
    
    printVector(solution, "Solution x");
    cout << "Expected: [1.0, 1.0, 3.0]" << endl;
    
    if (verifySolution(A, solution, b)) {
        cout << "Solution VERIFIED!" << endl;
    } else {
        cout << "ERROR: Solution does not satisfy the system!" << endl;
    }
}

void tryDirectSolution3x3() {
    cout << "\n=== Manual Solution Attempt ===\n" << endl;
    
    Matrix A(3, 3);
    A(1, 1) = 3.0; A(1, 2) = 2.0; A(1, 3) = 1.0;
    A(2, 1) = 2.0; A(2, 2) = 5.0; A(2, 3) = 3.0;
    A(3, 1) = 1.0; A(3, 2) = 1.0; A(3, 3) = 2.0;
    
    Vector b(3);
    b(1) = 10.0;
    b(2) = 15.0;
    b(3) = 8.0;
    
    Matrix aug(3, 4);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            aug(i, j) = A(i, j);
        }
        aug(i, 4) = b(i);
    }
    
    printMatrix(aug, "Augmented Matrix [A|b]");
    
    for (int i = 1; i <= 3; i++) {
        int maxRow = i;
        for (int k = i + 1; k <= 3; k++) {
            if (fabs(aug(k, i)) > fabs(aug(maxRow, i))) {
                maxRow = k;
            }
        }
        
        cout << "Pivot position (" << i << "," << i << "), value = " << aug(maxRow, i) << endl;
        
        if (maxRow != i) {
            cout << "Swapping rows " << i << " and " << maxRow << endl;
            for (int j = 1; j <= 4; j++) {
                double temp = aug(i, j);
                aug(i, j) = aug(maxRow, j);
                aug(maxRow, j) = temp;
            }
        }
        
        printMatrix(aug, "After row swap");
        
        for (int k = i + 1; k <= 3; k++) {
            double factor = aug(k, i) / aug(i, i);
            for (int j = i; j <= 4; j++) {
                aug(k, j) -= factor * aug(i, j);
            }
        }
        
        printMatrix(aug, "After elimination");
    }
    
    Vector x(3);
    for (int i = 3; i >= 1; i--) {
        double sum = 0.0;
        for (int j = i + 1; j <= 3; j++) {
            sum += aug(i, j) * x(j);
        }
        x(i) = (aug(i, 4) - sum) / aug(i, i);
    }
    
    printVector(x, "Manual solution");
    if (verifySolution(A, x, b)) {
        cout << "Manual solution VERIFIED!" << endl;
    } else {
        cout << "ERROR: Manual solution does not satisfy the system!" << endl;
    }
}

int main() {
    try {
        cout << "=== SIMPLE LINEAR SYSTEM TEST ===\n" << endl;
        solveAndDebug2x2();
        solveAndDebug3x3();
        tryDirectSolution3x3();
        return 0;
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}