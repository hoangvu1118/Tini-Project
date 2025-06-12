#include <iostream>
#include <Vector.h>
#include <cassert>
#include <cmath>

using namespace std;

bool isEqual(double a, double b, double epsilon = 1e-10) {
    return fabs(a - b) < epsilon;
}

bool areEqual(Vector& v1, Vector& v2) {
    if (v1.size() != v2.size())
        return false;

    for (int i = 0; i < v1.size(); i++) {
        if (!isEqual(v1[i], v2[i]))
            return false;
    }
    return true;
}

void testConstructor() {
    cout << "Testing constructors..." << endl;

    Vector v1(3);
    assert(v1.size() == 3);
    assert(isEqual(v1[0], 0.0));
    assert(isEqual(v1[1], 0.0));
    assert(isEqual(v1[2], 0.0));

    Vector v2(0);
    assert(v2.size() == 1);

    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;
    Vector v3(v1);
    assert(areEqual(v1, v3));

    v3[0] = 10.0;
    assert(!areEqual(v1, v3));

    cout << "Constructor tests passed!" << endl;
}

void testAssignment() {
    cout << "Testing assignment operator..." << endl;

    Vector v1(3);
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;

    Vector v2(2);
    v2 = v1;
    assert(v2.size() == 3);
    assert(areEqual(v1, v2));

    v1 = v1;
    assert(isEqual(v1[0], 1.0));
    assert(isEqual(v1[1], 2.0));
    assert(isEqual(v1[2], 3.0));

    cout << "Assignment tests passed!" << endl;
}

void testUnaryOperator() {
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

void testBinaryOperators() {
    cout << "Testing binary operators..." << endl;

    Vector v1(3);
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;

    Vector v2(3);
    v2[0] = 4.0;
    v2[1] = 5.0;
    v2[2] = 6.0;

    Vector v3 = v1 + v2;
    assert(isEqual(v3[0], 5.0));
    assert(isEqual(v3[1], 7.0));
    assert(isEqual(v3[2], 9.0));

    Vector v4 = v2 - v1;
    assert(isEqual(v4[0], 3.0));
    assert(isEqual(v4[1], 3.0));
    assert(isEqual(v4[2], 3.0));

    Vector v5 = v1 * 2.0;
    assert(isEqual(v5[0], 2.0));
    assert(isEqual(v5[1], 4.0));
    assert(isEqual(v5[2], 6.0));

    Vector v6(2);
    cout << "Testing error handling for mismatched sizes:" << endl;
    Vector v7 = v1 + v6;
    Vector v8 = v1 - v6;

    cout << "Binary operator tests passed!" << endl;
}

void testDotProduct() {
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
    assert(isEqual(dot, 32.0));

    Vector v3(2);
    double invalid_dot = v1.dot(v3);
    assert(isEqual(invalid_dot, 0.0));

    cout << "Dot product tests passed!" << endl;
}

void testIndexing() {
    cout << "Testing indexing operators..." << endl;

    Vector v1(3);
    v1[0] = 10.0;
    v1[1] = 20.0;
    v1[2] = 30.0;

    assert(isEqual(v1[0], 10.0));
    assert(isEqual(v1[1], 20.0));
    assert(isEqual(v1[2], 30.0));

    assert(isEqual(v1(1), 10.0));
    assert(isEqual(v1(2), 20.0));
    assert(isEqual(v1(3), 30.0));

    cout << "Testing boundary conditions:" << endl;
    v1[-1] = 100.0;
    v1[3] = 100.0;
    v1(0) = 200.0;
    v1(4) = 200.0;

    cout << "Indexing tests passed!" << endl;
}

int main() {
    try {
        cout << "Running Vector class tests..." << endl;

        testConstructor();
        testAssignment();
        testUnaryOperator();
        testBinaryOperators();
        testDotProduct();
        testIndexing();

        cout << "All tests passed successfully!" << endl;
        return 0;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
}