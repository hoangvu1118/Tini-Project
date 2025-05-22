#include <iostream>
#include <Vector.h>
using namespace std;

// Constructor
Vector::Vector(int size) : mSize(size) {
    if (size <= 0) mSize = 1;
    mData = new double[mSize]();
}

// Copy Constructor
Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = other.mData[i];
    }
}

// Destructor
Vector::~Vector() {
    delete[] mData;
}

// Assignment Operator
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }
    return *this;
}

// Unary Operator Overload
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = -mData[i];
    }
    return result;
}

// Binary Operator Overloads
Vector Vector::operator+(const Vector& other) const {
    if (mSize != other.mSize) {
        cout << "Error: Vector sizes don't match for addition" << endl;
        return Vector(mSize);
    }
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] + other.mData[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    if (mSize != other.mSize) {
        cout << "Error: Vector sizes don't match for subtraction" << endl;
        return Vector(mSize);
    }
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] - other.mData[i];
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i) {
        result.mData[i] = mData[i] * scalar;
    }
    return result;
}

// Dot Product
double Vector::dot(const Vector& other) const {
    if (mSize != other.mSize) {
        cout << "Error: Vector sizes don't match for dot product" << endl;
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 0; i < mSize; ++i) {
        sum += mData[i] * other.mData[i];
    }
    return sum;
}

// Square Bracket Operator Overload for index checking
double& Vector::operator[](int index) {
    if (index < 0 || index >= mSize) {
        cout << "Error: Index out of bounds for operator[]" << endl;
        return mData[0];
    }
    return mData[index];
}

// Round Bracket Operator Overload for one-based indexing
double& Vector::operator()(int index) {
    if (index <= 0 || index > mSize) {
        cout << "Error: Index out of bounds for operator()" << endl;
        return mData[0];
    }
    return mData[index - 1];
}

// Get size of the vector
int Vector::size() const {
    return mSize;
}

