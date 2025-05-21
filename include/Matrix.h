# pragma once

#include <iostream>
using namespace std;

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    // Constructor
    Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {}

    // Copy Constructor
    Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {}

    // Destructor
    ~Matrix() {}

    // Accessors
    int numRows() const { return mNumRows; }
    int numCols() const { return mNumCols; }

    // Overloaded round bracket operator for one-based indexing
    double& operator()(int i, int j) {}

    // Overloaded assignment operator
    Matrix& operator=(const Matrix& other) {}

    // Overloaded unary and binary operators for matrix operations
    double determinant() const;

    Matrix inverse() const;

    Matrix pseudoInverse() const;
};
