#include <iostream>
#include <Vector.h>
#include <Matrix.h>
#include <cassert>
#include <cmath>

using namespace std;

// Helper function to check if two doubles are approximately equal
bool isEqual(double a, double b, double epsilon = 1e-9)
{
    return fabs(a - b) < epsilon;
}

// Helper function for vector comparison
bool areVectorsEqual(const Vector &v1, const Vector &v2, double epsilon = 1e-9)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (int i = 1; i <= v1.size(); i++)
    {
        if (!isEqual(const_cast<Vector &>(v1)(i), const_cast<Vector &>(v2)(i), epsilon))
        {
            return false;
        }
    }
    return true;
}

void printVector(const Vector &v, const string &name)
{
    cout << name << ": [";
    for (int i = 1; i <= v.size(); i++)
    {
        cout << const_cast<Vector &>(v)(i);
        if (i < v.size())
            cout << ", ";
    }
    cout << "]" << endl;
}

int main()
{
    cout << "Testing Matrix-Vector Multiplication" << endl;
    cout << "==================================" << endl;

    // Test 1: Simple 2x2 matrix with 2-element vector
    Matrix A(2, 2);
    A(1, 1) = 1;
    A(1, 2) = 2;
    A(2, 1) = 3;
    A(2, 2) = 4;

    Vector x(2);
    x(1) = 5;
    x(2) = 6;

    cout << "Matrix A:" << endl;
    for (int i = 1; i <= A.numRows(); i++)
    {
        for (int j = 1; j <= A.numCols(); j++)
        {
            cout << A(i, j) << " ";
        }
        cout << endl;
    }

    printVector(x, "Vector x");

    Vector result = A * x;
    printVector(result, "A * x");

    // Expected result: [1*5 + 2*6, 3*5 + 4*6] = [17, 39]
    Vector expected(2);
    expected(1) = 17;
    expected(2) = 39;

    assert(areVectorsEqual(result, expected));
    cout << "Test 1 Passed: 2x2 matrix * 2-element vector" << endl;

    // Test 2: 3x3 matrix with 3-element vector
    Matrix B(3, 3);
    B(1, 1) = 1;
    B(1, 2) = 0;
    B(1, 3) = 2;
    B(2, 1) = -1;
    B(2, 2) = 3;
    B(2, 3) = 1;
    B(3, 1) = 0;
    B(3, 2) = 1;
    B(3, 3) = -1;

    Vector y(3);
    y(1) = 2;
    y(2) = 1;
    y(3) = 0;

    cout << "\nMatrix B:" << endl;
    for (int i = 1; i <= B.numRows(); i++)
    {
        for (int j = 1; j <= B.numCols(); j++)
        {
            cout << B(i, j) << " ";
        }
        cout << endl;
    }

    printVector(y, "Vector y");

    Vector result2 = B * y;
    printVector(result2, "B * y");

    // Expected result: [1*2 + 0*1 + 2*0, -1*2 + 3*1 + 1*0, 0*2 + 1*1 + -1*0] = [2, 1, 1]
    Vector expected2(3);
    expected2(1) = 2;
    expected2(2) = 1;
    expected2(3) = 1;

    assert(areVectorsEqual(result2, expected2));
    cout << "Test 2 Passed: 3x3 matrix * 3-element vector" << endl;

    // Test 3: Non-square matrix
    Matrix C(2, 3);
    C(1, 1) = 1;
    C(1, 2) = 2;
    C(1, 3) = 3;
    C(2, 1) = 4;
    C(2, 2) = 5;
    C(2, 3) = 6;

    Vector z(3);
    z(1) = 7;
    z(2) = 8;
    z(3) = 9;

    cout << "\nMatrix C:" << endl;
    for (int i = 1; i <= C.numRows(); i++)
    {
        for (int j = 1; j <= C.numCols(); j++)
        {
            cout << C(i, j) << " ";
        }
        cout << endl;
    }

    printVector(z, "Vector z");

    Vector result3 = C * z;
    printVector(result3, "C * z");

    // Expected result: [1*7 + 2*8 + 3*9, 4*7 + 5*8 + 6*9] = [50, 122]
    Vector expected3(2);
    expected3(1) = 50;
    expected3(2) = 122;

    assert(areVectorsEqual(result3, expected3));
    cout << "Test 3 Passed: 2x3 matrix * 3-element vector" << endl;

    cout << "\nAll tests passed successfully!" << endl;

    return 0;
}
