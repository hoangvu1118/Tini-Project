# pragma once

#include <iostream>
using namespace std;

class Vector {
private:
    int mSize;
    double* mData;

public:
    // Constructor
    Vector(int size) : mSize(size) {
        if (size <= 0) mSize = 1;
        mData = new double[mSize]();
    }

    // Copy Constructor
    Vector(const Vector& other) : mSize(other.mSize) {
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }

    // Destructor
    ~Vector() {
        delete[] mData;
    }

    // Assignment Operator
    Vector& operator=(const Vector& other) {
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
    Vector operator-() const {
        Vector result(mSize);
        for (int i = 0; i < mSize; ++i) {
            result.mData[i] = -mData[i];
        }
        return result;
    }

    // Binary Operator Overloads
    Vector operator+(const Vector& other) const {
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

    Vector operator-(const Vector& other) const {
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

    Vector operator*(double scalar) const {
        Vector result(mSize);
        for (int i = 0; i < mSize; ++i) {
            result.mData[i] = mData[i] * scalar;
        }
        return result;
    }
    
    // Square Bracket Operator Overload for index checking
    double& operator[](int index) {
        if (index < 0 || index >= mSize) {
            cout << "Error: Index out of bounds for operator[]" << endl;
            return mData[0];
        }
        return mData[index];
    }

    // Round Bracket Operator Overload for one-based indexing
    double& operator()(int index) {
        if (index <= 0 || index > mSize) {
            cout << "Error: Index out of bounds for operator()" << endl;
            return mData[0];
        }
        return mData[index - 1];
    }
    

    // Get size of the vector
    int size() const {
        return mSize;
    }
};
