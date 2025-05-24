#include <iostream>
#include <LinearSystem.h>
#include <PosSymLinSystem.h> // For Tikhonov, as A^T A is symmetric
#include <Vector.h>
#include <Matrix.h>
#include <cmath>
#include <stdexcept>

using namespace std;

// Function to solve ill-posed problems using Moore-Penrose pseudoinverse
Vector solvePseudoinverse(Matrix& A, Vector& b) {
    cout << "\n--- Solving with Moore-Penrose Pseudoinverse ---" << endl;
    Matrix Aplus = A.pseudoInverse();

    if (Aplus.numCols() != b.size()) {
        throw invalid_argument("Dimension mismatch between pseudoinverse and vector b for multiplication.");
    }
    Vector x = Aplus * b;
    
    return x;
}

// Function to solve ill-posed problems using Tikhonov regularization
// Solves (A^T A + alpha^2 I) x = A^T b
Vector solveTikhonov(Matrix& A, Vector& b, double alpha) {
    cout << "\n--- Solving with Tikhonov Regularization (alpha = " << alpha << ") ---" << endl;
    if (alpha <= 0) {
        throw invalid_argument("Regularization parameter alpha must be positive.");
    }

    Matrix AT = A.transpose();
    Matrix ATA = AT * A;

    int n_cols = A.numCols();
    Matrix I(n_cols, n_cols);
    for (int i = 1; i <= n_cols; ++i) {
        I(i, i) = 1.0;
    }

    Matrix ATA_plus_alpha2I = ATA + (I * (alpha * alpha));

    Vector ATb = AT * b;

    // Check if ATA_plus_alpha2I is square and compatible with ATb
    if (ATA_plus_alpha2I.numRows() != ATA_plus_alpha2I.numCols()) {
         throw runtime_error("Tikhonov: (A^T A + alpha^2 I) is not square.");
    }
    if (ATA_plus_alpha2I.numRows() != ATb.size()) {
        throw runtime_error("Tikhonov: Dimension mismatch for solving regularized system.");
    }

    LinearSystem regularized_system(&ATA_plus_alpha2I, &ATb);
    Vector x = regularized_system.Solve();

    return x;
}

// Helper to print vectors
void printVector(const Vector& vec, const string& name) {
    cout << name << ": [";
    for (int i = 1; i <= vec.size(); ++i) {
        cout << const_cast<Vector&>(vec)(i) << (i == vec.size() ? "" : ", ");
    }
    cout << "]" << endl;
}

// Helper to print matrices
void printMatrix(const Matrix& mat, const string& name) {
    cout << name << ":" << endl;
    for (int i = 1; i <= mat.numRows(); ++i) {
        cout << "[ ";
        for (int j = 1; j <= mat.numCols(); ++j) {
            cout << mat(i, j) << (j == mat.numCols() ? " " : ", ");
        }
        cout << "]" << endl;
    }
}


int main() {
    try {
        // --- Example 1: Over-determined system (more equations than unknowns) ---
        cout << "====== Example 1: Over-determined System ======" << endl;
        // 2x = 3
        // 3x = 4
        // 4x = 5
        // Expect x to be around 1.2 - 1.3
        Matrix A_over(3, 1);
        A_over(1, 1) = 2;
        A_over(2, 1) = 3;
        A_over(3, 1) = 4;

        Vector b_over(3);
        b_over(1) = 3;
        b_over(2) = 4;
        b_over(3) = 5;

        printMatrix(A_over, "A_over");
        printVector(b_over, "b_over");

        Vector x_pseudo_over = solvePseudoinverse(A_over, b_over);
        printVector(x_pseudo_over, "x_pseudoinverse_over");
        printVector(A_over * x_pseudo_over, "A*x_pseudo_over");


        Vector x_tikhonov_over = solveTikhonov(A_over, b_over, 0.1);
        printVector(x_tikhonov_over, "x_tikhonov_over (alpha=0.1)");
        printVector(A_over * x_tikhonov_over, "A*x_tikhonov_over");
        cout << endl;

        // --- Example 2: Under-determined system (more unknowns than equations) ---
        cout << "====== Example 2: Under-determined System ======" << endl;
        // x + 2y = 3
        // Expect a solution with minimum norm from pseudoinverse
        Matrix A_under(1, 2);
        A_under(1, 1) = 1;
        A_under(1, 2) = 2;

        Vector b_under(1);
        b_under(1) = 3;

        printMatrix(A_under, "A_under");
        printVector(b_under, "b_under");

        Vector x_pseudo_under = solvePseudoinverse(A_under, b_under);
        printVector(x_pseudo_under, "x_pseudoinverse_under (min norm solution)");
        printVector(A_under * x_pseudo_under, "A*x_pseudo_under");


        Vector x_tikhonov_under = solveTikhonov(A_under, b_under, 0.1);
        printVector(x_tikhonov_under, "x_tikhonov_under (alpha=0.1)");
        printVector(A_under * x_tikhonov_under, "A*x_tikhonov_under");
        cout << endl;

        // --- Example 3: A slightly larger under-determined system ---
        cout << "====== Example 3: 2x3 Under-determined System ======" << endl;
        // x + y + z = 6
        // x - y + 2z = 5
        Matrix A_under2(2, 3);
        A_under2(1,1) = 1; A_under2(1,2) = 1; A_under2(1,3) = 1;
        A_under2(2,1) = 1; A_under2(2,2) = -1; A_under2(2,3) = 2;

        Vector b_under2(2);
        b_under2(1) = 6;
        b_under2(2) = 5;

        printMatrix(A_under2, "A_under2");
        printVector(b_under2, "b_under2");

        Vector x_pseudo_under2 = solvePseudoinverse(A_under2, b_under2);
        printVector(x_pseudo_under2, "x_pseudoinverse_under2");
        printVector(A_under2 * x_pseudo_under2, "A*x_pseudo_under2");

        Vector x_tikhonov_under2 = solveTikhonov(A_under2, b_under2, 0.01);
        printVector(x_tikhonov_under2, "x_tikhonov_under2 (alpha=0.01)");
        printVector(A_under2 * x_tikhonov_under2, "A*x_tikhonov_under2");


    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}



