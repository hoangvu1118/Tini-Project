#include "Header-Files/Matrix.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

// Helper function to print matrices
void printMatrix(const Matrix& m, const std::string& name) {
    std::cout << name << " (" << m.numRows() << "x" << m.numCols() << "):" << std::endl;
    for (int i = 1; i <= m.numRows(); i++) {
        std::cout << "  ";
        for (int j = 1; j <= m.numCols(); j++) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << m(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Helper function to check if two matrices are approximately equal
bool matricesEqual(const Matrix& a, const Matrix& b, double epsilon = 1e-9) {
    if (a.numRows() != b.numRows() || a.numCols() != b.numCols()) {
        return false;
    }
    
    for (int i = 1; i <= a.numRows(); i++) {
        for (int j = 1; j <= a.numCols(); j++) {
            if (std::fabs(a(i, j) - b(i, j)) > epsilon) {
                return false;
            }
        }
    }
    return true;
}

// Function to test basic matrix operations
void testBasicOperations() {
    std::cout << "=== Testing Basic Matrix Operations ===" << std::endl;
    
    // Create a 2x3 matrix
    Matrix a(2, 3);
    a(1, 1) = 1.0; a(1, 2) = 2.0; a(1, 3) = 3.0;
    a(2, 1) = 4.0; a(2, 2) = 5.0; a(2, 3) = 6.0;
    printMatrix(a, "Matrix A");
    
    // Test copy constructor
    Matrix b(a);
    printMatrix(b, "Matrix B (copy of A)");
    assert(matricesEqual(a, b));
    
    // Test assignment operator
    Matrix c(3, 3);
    c = a;
    printMatrix(c, "Matrix C (assigned from A)");
    assert(matricesEqual(a, c));
    
    // Test element access and modification
    b(1, 2) = 20.0;
    printMatrix(b, "Matrix B after modification");
    assert(b(1, 2) == 20.0);
    
    std::cout << "All basic operations passed!" << std::endl << std::endl;
}

// Function to test arithmetic operations
void testArithmeticOperations() {
    std::cout << "=== Testing Matrix Arithmetic Operations ===" << std::endl;
    
    // Create matrices
    Matrix a(2, 2);
    a(1, 1) = 1.0; a(1, 2) = 2.0;
    a(2, 1) = 3.0; a(2, 2) = 4.0;
    printMatrix(a, "Matrix A");
    
    Matrix b(2, 2);
    b(1, 1) = 5.0; b(1, 2) = 6.0;
    b(2, 1) = 7.0; b(2, 2) = 8.0;
    printMatrix(b, "Matrix B");
    
    // Test addition
    Matrix c = a + b;
    printMatrix(c, "A + B");
    
    // Expected result
    Matrix expectedSum(2, 2);
    expectedSum(1, 1) = 6.0; expectedSum(1, 2) = 8.0;
    expectedSum(2, 1) = 10.0; expectedSum(2, 2) = 12.0;
    assert(matricesEqual(c, expectedSum));
    
    // Test subtraction
    Matrix d = a - b;
    printMatrix(d, "A - B");
    
    // Expected result
    Matrix expectedDiff(2, 2);
    expectedDiff(1, 1) = -4.0; expectedDiff(1, 2) = -4.0;
    expectedDiff(2, 1) = -4.0; expectedDiff(2, 2) = -4.0;
    assert(matricesEqual(d, expectedDiff));
    
    // Test unary minus
    Matrix e = -a;
    printMatrix(e, "-A");
    
    // Expected result
    Matrix expectedNeg(2, 2);
    expectedNeg(1, 1) = -1.0; expectedNeg(1, 2) = -2.0;
    expectedNeg(2, 1) = -3.0; expectedNeg(2, 2) = -4.0;
    assert(matricesEqual(e, expectedNeg));
    
    // Test scalar multiplication
    Matrix f = a * 2.0;
    printMatrix(f, "A * 2.0");
    
    // Expected result
    Matrix expectedScalarMult(2, 2);
    expectedScalarMult(1, 1) = 2.0; expectedScalarMult(1, 2) = 4.0;
    expectedScalarMult(2, 1) = 6.0; expectedScalarMult(2, 2) = 8.0;
    assert(matricesEqual(f, expectedScalarMult));
    
    std::cout << "All arithmetic operations passed!" << std::endl << std::endl;
}

// Function to test matrix multiplication
void testMatrixMultiplication() {
    std::cout << "=== Testing Matrix Multiplication ===" << std::endl;
    
    // Create matrices
    Matrix a(2, 3);
    a(1, 1) = 1.0; a(1, 2) = 2.0; a(1, 3) = 3.0;
    a(2, 1) = 4.0; a(2, 2) = 5.0; a(2, 3) = 6.0;
    printMatrix(a, "Matrix A (2x3)");
    
    Matrix b(3, 2);
    b(1, 1) = 7.0; b(1, 2) = 8.0;
    b(2, 1) = 9.0; b(2, 2) = 10.0;
    b(3, 1) = 11.0; b(3, 2) = 12.0;
    printMatrix(b, "Matrix B (3x2)");
    
    // Test matrix multiplication
    Matrix c = a * b;
    printMatrix(c, "A * B");
    
    // Expected result (manually calculated)
    Matrix expectedProduct(2, 2);
    expectedProduct(1, 1) = 58.0; expectedProduct(1, 2) = 64.0;
    expectedProduct(2, 1) = 139.0; expectedProduct(2, 2) = 154.0;
    assert(matricesEqual(c, expectedProduct));
    
    std::cout << "Matrix multiplication passed!" << std::endl << std::endl;
}

// Function to test matrix operations (determinant, inverse)
void testMatrixOperations() {
    std::cout << "=== Testing Advanced Matrix Operations ===" << std::endl;
    
    // Create a square matrix
    Matrix a(3, 3);
    a(1, 1) = 4.0; a(1, 2) = 3.0; a(1, 3) = 8.0;
    a(2, 1) = 9.0; a(2, 2) = 4.0; a(2, 3) = 7.0;
    a(3, 1) = 3.0; a(3, 2) = 5.0; a(3, 3) = 2.0;
    printMatrix(a, "Matrix A");
    
    // Test determinant
    double det = a.determinant();
    std::cout << "Determinant of A: " << det << std::endl;
    assert(std::fabs(det - (-189.0)) < 1e-9);
    
    // Test inverse
    Matrix aInv = a.inverse();
    printMatrix(aInv, "A^(-1)");
    
    // Verify A * A^(-1) = I
    Matrix identity = a * aInv;
    printMatrix(identity, "A * A^(-1)");
    
    // Expected identity matrix
    Matrix expectedIdentity(3, 3);
    expectedIdentity(1, 1) = 1.0; expectedIdentity(1, 2) = 0.0; expectedIdentity(1, 3) = 0.0;
    expectedIdentity(2, 1) = 0.0; expectedIdentity(2, 2) = 1.0; expectedIdentity(2, 3) = 0.0;
    expectedIdentity(3, 1) = 0.0; expectedIdentity(3, 2) = 0.0; expectedIdentity(3, 3) = 1.0;
    
    // Check if matrix is approximately identity (allow for floating point errors)
    bool isIdentity = matricesEqual(identity, expectedIdentity, 1e-6);
    std::cout << "A * A^(-1) is " << (isIdentity ? "identity" : "NOT identity") << std::endl;
    assert(isIdentity);
    
    std::cout << "All advanced operations passed!" << std::endl << std::endl;
}

// Function to test pseudoinverse
void testPseudoInverse() {
    std::cout << "=== Testing Pseudoinverse ===" << std::endl;
    
    // Test with non-square matrix (more rows than columns)
    Matrix a(3, 2);
    a(1, 1) = 1.0; a(1, 2) = 2.0;
    a(2, 1) = 3.0; a(2, 2) = 4.0;
    a(3, 1) = 5.0; a(3, 2) = 6.0;
    printMatrix(a, "Matrix A (3x2)");
    
    Matrix pseudoInv = a.pseudoInverse();
    printMatrix(pseudoInv, "Pseudoinverse of A");
    
    // Check A * A⁺ * A = A
    Matrix verifyPseudo = a * pseudoInv * a;
    printMatrix(verifyPseudo, "A * A⁺ * A");
    
    // Should be approximately equal to A
    bool isValid = matricesEqual(verifyPseudo, a, 1e-6);
    std::cout << "A * A⁺ * A is " << (isValid ? "equal to A" : "NOT equal to A") << std::endl;
    assert(isValid);
    
    std::cout << "Pseudoinverse test passed!" << std::endl << std::endl;
}

int main() {
    try {
        testBasicOperations();
        testArithmeticOperations();
        testMatrixMultiplication();
        testMatrixOperations();
        testPseudoInverse();
        
        std::cout << "All tests passed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
    
    return 0;
}
