#include <iostream>
#include <Vector.h>
#include <cassert>
#include <cmath>

using namespace std;

// Helper function to check if two doubles are approximately equal
bool isEqual(double a, double b, double epsilon = 1e-10)
{
    return fabs(a - b) < epsilon;
}

// Helper function to check if two vectors are equal
bool areEqual(const Vector &v1, const Vector &v2)
{
    if (v1.size() != v2.size())
        return false;

    for (int i = 0; i < v1.size(); i++)
    {
        // Need to cast away constness since operator[] is not const
        if (!isEqual(const_cast<Vector &>(v1)[i], const_cast<Vector &>(v2)[i]))
            return false;
    }
    return true;
}

void testConstructor()
{
    cout << "Testing constructors..." << endl;

    // Test basic constructor
    Vector v1(3);
    assert(v1.size() == 3);
    assert(isEqual(v1[0], 0.0));
    assert(isEqual(v1[1], 0.0));
    assert(isEqual(v1[2], 0.0));

    // Test constructor with size <= 0
    Vector v2(0); // Should become size 1
    assert(v2.size() == 1);

    // Test copy constructor
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;
    Vector v3(v1);
    assert(areEqual(v1, v3));

    // Verify deep copy
    v3[0] = 10.0;
    assert(!areEqual(v1, v3));

    cout << "Constructor tests passed!" << endl;
}

void testAssignment()
{
    cout << "Testing assignment operator..." << endl;

    Vector v1(3);
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;

    Vector v2(2);
    v2 = v1; // Should resize and copy
    assert(v2.size() == 3);
    assert(areEqual(v1, v2));

    // Self-assignment
    v1 = v1;
    assert(v1[0] == 1.0);
    assert(v1[1] == 2.0);
    assert(v1[2] == 3.0);

    cout << "Assignment tests passed!" << endl;
}

void testUnaryOperator()
{
    cout << "Testing unary operator..." << endl;

    Vector v1(3);
    v1[0] = 1.0;
    v1[1] = -2.0;
    v1[2] = 3.0;

    Vector v2 = -v1;
    assert(isEqual(v2[0], -1.0));
    assert(isEqual(v2[1], 2.0));
    assert(isEqual(v2[2], -3.0));

    cout << "Unary operator tests passed!" << endl;
}

void testBinaryOperators()
{
    cout << "Testing binary operators..." << endl;

    Vector v1(3);
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;

    Vector v2(3);
    v2[0] = 4.0;
    v2[1] = 5.0;
    v2[2] = 6.0;

    // Addition
    Vector v3 = v1 + v2;
    assert(isEqual(v3[0], 5.0));
    assert(isEqual(v3[1], 7.0));
    assert(isEqual(v3[2], 9.0));

    // Subtraction
    Vector v4 = v2 - v1;
    assert(isEqual(v4[0], 3.0));
    assert(isEqual(v4[1], 3.0));
    assert(isEqual(v4[2], 3.0));

    // Scalar multiplication
    Vector v5 = v1 * 2.0;
    assert(isEqual(v5[0], 2.0));
    assert(isEqual(v5[1], 4.0));
    assert(isEqual(v5[2], 6.0));

    // Testing with incompatible sizes
    Vector v6(2);
    Vector v7 = v1 + v6; // Should return Vector of size 3 and print error
    Vector v8 = v1 - v6; // Should return Vector of size 3 and print error

    cout << "Binary operator tests passed!" << endl;
}

void testDotProduct()
{
    cout << "Testing dot product..." << endl;

    Vector v1(3);
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;

    Vector v2(3);
    v2[0] = 4.0;
    v2[1] = 5.0;
    v2[2] = 6.0;

    double dot = v1.dot(v2);
    assert(isEqual(dot, 32.0)); // 1*4 + 2*5 + 3*6

    // Test with incompatible sizes
    Vector v3(2);
    double invalid_dot = v1.dot(v3); // Should return 0.0 and print error
    assert(isEqual(invalid_dot, 0.0));

    cout << "Dot product tests passed!" << endl;
}

void testIndexing()
{
    cout << "Testing indexing operators..." << endl;

    Vector v1(3);

    // Zero-based indexing with []
    v1[0] = 10.0;
    v1[1] = 20.0;
    v1[2] = 30.0;
    assert(isEqual(v1[0], 10.0));
    assert(isEqual(v1[1], 20.0));
    assert(isEqual(v1[2], 30.0));

    // One-based indexing with ()
    assert(isEqual(v1(1), 10.0));
    assert(isEqual(v1(2), 20.0));
    assert(isEqual(v1(3), 30.0));

    // Test out-of-bounds access with []
    // These should print error messages but return the first element
    v1[-1] = 100.0; // Should print error
    v1[3] = 100.0;  // Should print error

    // Test out-of-bounds access with ()
    // These should print error messages but return the first element
    v1(0) = 200.0; // Should print error
    v1(4) = 200.0; // Should print error

    cout << "Indexing tests passed!" << endl;
}

int main()
{
    cout << "Running Vector class tests..." << endl;

    testConstructor();
    testAssignment();
    testUnaryOperator();
    testBinaryOperators();
    testDotProduct();
    testIndexing();

    cout << "All tests passed successfully!" << endl;
    return 0;
}
