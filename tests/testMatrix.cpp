#include "Matrix.h" // Include your Matrix header file
#include <iostream>
#include <cassert>
#include <vector> // For comparing matrices
#include <cmath>  // For fabs

const double TEST_THRESHOLD = 1e-9; // A threshold for floating point comparisons in tests

// Helper function to print a matrix
void printMatrix(const Matrix& mat, const std::string& name) {
    std::cout << name << " (" << mat.numRows() << "x" << mat.numCols() << "):" << std::endl;
    for (int i = 1; i <= mat.numRows(); ++i) {
        for (int j = 1; j <= mat.numCols(); ++j) {
            std::cout << mat(i, j) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Helper function to compare two matrices for approximate equality
bool areMatricesEqual(const Matrix& m1, const Matrix& m2, double tolerance = TEST_THRESHOLD) {
    if (m1.numRows() != m2.numRows() || m1.numCols() != m2.numCols()) {
        return false;
    }
    for (int i = 1; i <= m1.numRows(); ++i) {
        for (int j = 1; j <= m1.numCols(); ++j) {
            if (fabs(m1(i, j) - m2(i, j)) > tolerance) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::cout << "--- Matrix Class Test Suite ---" << std::endl << std::endl;

    // Test 1: Constructor and Accessors
    std::cout << "Test 1: Constructor and Accessors" << std::endl;
    Matrix m1(3, 2);
    assert(m1.numRows() == 3);
    assert(m1.numCols() == 2);
    m1(1, 1) = 1.0;
    m1(2, 2) = 5.0;
    m1(3, 1) = 2.0;
    printMatrix(m1, "m1"); // Expected: [[1, 0], [0, 5], [2, 0]]
    std::cout << "Test 1 Passed." << std::endl << std::endl;

    // Test 2: Copy Constructor
    std::cout << "Test 2: Copy Constructor" << std::endl;
    Matrix m2 = m1;
    assert(areMatricesEqual(m1, m2));
    printMatrix(m2, "m2 (copy of m1)"); // Expected: [[1, 0], [0, 5], [2, 0]]
    // Modify m2 to ensure deep copy
    m2(1, 1) = 100.0;
    assert(!areMatricesEqual(m1, m2));
    printMatrix(m2, "m2 (modified)");
    printMatrix(m1, "m1 (original)"); // m1 should be unchanged
    std::cout << "Test 2 Passed." << std::endl << std::endl;

    // Test 3: Assignment Operator
    std::cout << "Test 3: Assignment Operator" << std::endl;
    Matrix m3(2, 2);
    m3(1, 1) = 1.0; m3(1, 2) = 2.0;
    m3(2, 1) = 3.0; m3(2, 2) = 4.0;
    printMatrix(m3, "m3 initial");

    Matrix m4(3, 3); // Different dimensions
    m4 = m3; // Assignment
    assert(m4.numRows() == 2 && m4.numCols() == 2);
    assert(areMatricesEqual(m3, m4));
    printMatrix(m4, "m4 (assigned from m3)"); // Expected: [[1, 2], [3, 4]]

    // Self-assignment
    m3 = m3;
    assert(areMatricesEqual(m3, m4)); // Should still be equal
    printMatrix(m3, "m3 after self-assignment");
    std::cout << "Test 3 Passed." << std::endl << std::endl;

    // Test 4: Unary Plus and Minus
    std::cout << "Test 4: Unary Plus and Minus" << std::endl;
    Matrix m_unary(2, 2);
    m_unary(1, 1) = 1.0; m_unary(1, 2) = -2.0;
    m_unary(2, 1) = 3.0; m_unary(2, 2) = -4.0;
    printMatrix(m_unary, "m_unary");

    Matrix m_plus = +m_unary;
    printMatrix(m_plus, "m_plus (+m_unary)");
    assert(areMatricesEqual(m_unary, m_plus));

    Matrix m_minus = -m_unary;
    printMatrix(m_minus, "m_minus (-m_unary)");
    Matrix expected_minus(2, 2);
    expected_minus(1, 1) = -1.0; expected_minus(1, 2) = 2.0;
    expected_minus(2, 1) = -3.0; expected_minus(2, 2) = 4.0;
    assert(areMatricesEqual(m_minus, expected_minus));
    std::cout << "Test 4 Passed." << std::endl << std::endl;

    // Test 5: Matrix Addition
    std::cout << "Test 5: Matrix Addition" << std::endl;
    Matrix A(2, 2);
    A(1, 1) = 1; A(1, 2) = 2;
    A(2, 1) = 3; A(2, 2) = 4;
    printMatrix(A, "A");

    Matrix B(2, 2);
    B(1, 1) = 5; B(1, 2) = 6;
    B(2, 1) = 7; B(2, 2) = 8;
    printMatrix(B, "B");

    Matrix C = A + B;
    printMatrix(C, "C = A + B"); // Expected: [[6, 8], [10, 12]]
    Matrix expected_C_add(2, 2);
    expected_C_add(1, 1) = 6; expected_C_add(1, 2) = 8;
    expected_C_add(2, 1) = 10; expected_C_add(2, 2) = 12;
    assert(areMatricesEqual(C, expected_C_add));
    std::cout << "Test 5 Passed." << std::endl << std::endl;

    // Test 6: Matrix Subtraction
    std::cout << "Test 6: Matrix Subtraction" << std::endl;
    Matrix D = A - B;
    printMatrix(D, "D = A - B"); // Expected: [[-4, -4], [-4, -4]]
    Matrix expected_D_sub(2, 2);
    expected_D_sub(1, 1) = -4; expected_D_sub(1, 2) = -4;
    expected_D_sub(2, 1) = -4; expected_D_sub(2, 2) = -4;
    assert(areMatricesEqual(D, expected_D_sub));
    std::cout << "Test 6 Passed." << std::endl << std::endl;

    // Test 7: Matrix Multiplication
    std::cout << "Test 7: Matrix Multiplication" << std::endl;
    Matrix E(2, 3);
    E(1, 1) = 1; E(1, 2) = 2; E(1, 3) = 3;
    E(2, 1) = 4; E(2, 2) = 5; E(2, 3) = 6;
    printMatrix(E, "E");

    Matrix F(3, 2);
    F(1, 1) = 7; F(1, 2) = 8;
    F(2, 1) = 9; F(2, 2) = 10;
    F(3, 1) = 11; F(3, 2) = 12;
    printMatrix(F, "F");

    Matrix G = E * F;
    printMatrix(G, "G = E * F"); // Expected: [[58, 64], [139, 154]]
    Matrix expected_G_mul(2, 2);
    expected_G_mul(1, 1) = 58; expected_G_mul(1, 2) = 64;
    expected_G_mul(2, 1) = 139; expected_G_mul(2, 2) = 154;
    assert(areMatricesEqual(G, expected_G_mul));

    // Test scalar multiplication
    Matrix H = E * 2.0;
    printMatrix(H, "H = E * 2.0");
    Matrix expected_H_scalar(2, 3);
    expected_H_scalar(1, 1) = 2; expected_H_scalar(1, 2) = 4; expected_H_scalar(1, 3) = 6;
    expected_H_scalar(2, 1) = 8; expected_H_scalar(2, 2) = 10; expected_H_scalar(2, 3) = 12;
    assert(areMatricesEqual(H, expected_H_scalar));
    std::cout << "Test 7 Passed." << std::endl << std::endl;

    // Test 8: Determinant
    std::cout << "Test 8: Determinant" << std::endl;
    Matrix det_mat1(2, 2);
    det_mat1(1, 1) = 4; det_mat1(1, 2) = 6;
    det_mat1(2, 1) = 3; det_mat1(2, 2) = 8;
    printMatrix(det_mat1, "det_mat1");
    double det1 = det_mat1.determinant();
    std::cout << "Determinant of det_mat1: " << det1 << std::endl; // Expected: 4*8 - 6*3 = 32 - 18 = 14
    assert(fabs(det1 - 14.0) < TEST_THRESHOLD);

    Matrix det_mat2(3, 3);
    det_mat2(1, 1) = 1; det_mat2(1, 2) = 2; det_mat2(1, 3) = 3;
    det_mat2(2, 1) = 4; det_mat2(2, 2) = 5; det_mat2(2, 3) = 6;
    det_mat2(3, 1) = 7; det_mat2(3, 2) = 8; det_mat2(3, 3) = 9;
    printMatrix(det_mat2, "det_mat2 (singular)");
    double det2 = det_mat2.determinant(); // Expected: 0 (rows are linearly dependent)
    std::cout << "Determinant of det_mat2: " << det2 << std::endl;
    assert(fabs(det2 - 0.0) < TEST_THRESHOLD);

    Matrix det_mat3(3, 3);
    det_mat3(1, 1) = 6; det_mat3(1, 2) = 1; det_mat3(1, 3) = 1;
    det_mat3(2, 1) = 4; det_mat3(2, 2) = -2; det_mat3(2, 3) = 5;
    det_mat3(3, 1) = 2; det_mat3(3, 2) = 8; det_mat3(3, 3) = 7;
    printMatrix(det_mat3, "det_mat3");
    double det3 = det_mat3.determinant();
    std::cout << "Determinant of det_mat3: " << det3 << std::endl; // Expected: -306
    assert(fabs(det3 - (-306.0)) < TEST_THRESHOLD);
    std::cout << "Test 8 Passed." << std::endl << std::endl;

    // Test 9: Inverse
    std::cout << "Test 9: Inverse" << std::endl;
    Matrix inv_mat1(2, 2);
    inv_mat1(1, 1) = 4; inv_mat1(1, 2) = 6;
    inv_mat1(2, 1) = 3; inv_mat1(2, 2) = 8;
    printMatrix(inv_mat1, "inv_mat1");
    try {
        Matrix inv1 = inv_mat1.inverse();
        printMatrix(inv1, "inv1 (Inverse of inv_mat1)");
        // Expected inverse: [[8/14, -6/14], [-3/14, 4/14]] = [[0.5714, -0.4286], [-0.2143, 0.2857]]
        Matrix expected_inv1(2, 2);
        expected_inv1(1, 1) = 8.0/14.0; expected_inv1(1, 2) = -6.0/14.0;
        expected_inv1(2, 1) = -3.0/14.0; expected_inv1(2, 2) = 4.0/14.0;
        assert(areMatricesEqual(inv1, expected_inv1));

        Matrix product = inv_mat1 * inv1;
        printMatrix(product, "inv_mat1 * inv1 (Should be Identity)");
        Matrix identity2x2(2,2);
        identity2x2(1,1) = 1.0; identity2x2(1,2) = 0.0;
        identity2x2(2,1) = 0.0; identity2x2(2,2) = 1.0;
        assert(areMatricesEqual(product, identity2x2));

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        assert(false && "Inverse of invertible matrix failed!");
    }

    std::cout << "Test 9a: Inverse of Singular Matrix (Expected Error)" << std::endl;
    try {
        Matrix singular_mat(2, 2);
        singular_mat(1, 1) = 1; singular_mat(1, 2) = 2;
        singular_mat(2, 1) = 2; singular_mat(2, 2) = 4; // Determinant is 0
        printMatrix(singular_mat, "singular_mat");
        Matrix inv_singular = singular_mat.inverse();
        // This line should not be reached
        assert(false && "Inverse of singular matrix did not throw an exception!");
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }
    std::cout << "Test 9 Passed." << std::endl << std::endl;

    // Test 10: PseudoInverse
    std::cout << "Test 10: PseudoInverse" << std::endl;

    // Case 1: Tall Matrix (mNumRows > mNumCols) - A⁺ = (AᵀA)⁻¹Aᵀ
    Matrix tall_mat(3, 2);
    tall_mat(1, 1) = 1; tall_mat(1, 2) = 2;
    tall_mat(2, 1) = 3; tall_mat(2, 2) = 4;
    tall_mat(3, 1) = 5; tall_mat(3, 2) = 6;
    printMatrix(tall_mat, "tall_mat (3x2)");

    try {
        Matrix pinv_tall = tall_mat.pseudoInverse();
        printMatrix(pinv_tall, "pseudoInverse of tall_mat");
        // For tall_mat, A⁺A should be identity.
        Matrix product_tall = pinv_tall * tall_mat;
        printMatrix(product_tall, "pseudoInverse(tall_mat) * tall_mat (should be Identity)");
        Matrix identity2x2(2,2);
        identity2x2(1,1) = 1.0; identity2x2(1,2) = 0.0;
        identity2x2(2,1) = 0.0; identity2x2(2,2) = 1.0;
        assert(areMatricesEqual(product_tall, identity2x2));

    } catch (const std::runtime_error& e) {
        std::cerr << "Error during pseudoInverse (tall): " << e.what() << std::endl;
        assert(false && "PseudoInverse for tall matrix failed!");
    }


    // Case 2: Wide Matrix (mNumRows < mNumCols) - A⁺ = Aᵀ(AAᵀ)⁻¹
    Matrix wide_mat(2, 3);
    wide_mat(1, 1) = 1; wide_mat(1, 2) = 2; wide_mat(1, 3) = 3;
    wide_mat(2, 1) = 4; wide_mat(2, 2) = 5; wide_mat(2, 3) = 6;
    printMatrix(wide_mat, "wide_mat (2x3)");

    try {
        Matrix pinv_wide = wide_mat.pseudoInverse();
        printMatrix(pinv_wide, "pseudoInverse of wide_mat");
        // For wide_mat, A*A⁺ should be identity.
        Matrix product_wide = wide_mat * pinv_wide;
        printMatrix(product_wide, "wide_mat * pseudoInverse(wide_mat) (should be Identity)");
        Matrix identity2x2(2,2);
        identity2x2(1,1) = 1.0; identity2x2(1,2) = 0.0;
        identity2x2(2,1) = 0.0; identity2x2(2,2) = 1.0;
        assert(areMatricesEqual(product_wide, identity2x2));

    } catch (const std::runtime_error& e) {
        std::cerr << "Error during pseudoInverse (wide): " << e.what() << std::endl;
        assert(false && "PseudoInverse for wide matrix failed!");
    }

    std::cout << "Test 10 Passed." << std::endl << std::endl;

    std::cout << "All tests completed successfully!" << std::endl;

    return 0;
}
