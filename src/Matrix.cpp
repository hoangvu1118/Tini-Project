# include "Matrix.h"
#include <iostream>
using namespace std;

// Constructor
Matrix::Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {
    if (numRows > 0 && numCols > 0){
        mNumRows = numRows;
        mNumCols = numCols;
    } else {
        mNumRows = 1;
        mNumCols = 1;
    }
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols]();
    }
}

// Copy Constructor
Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

// Destructor
Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i) {
        delete[] mData[i];
    }
    delete[] mData;
}

// Accessors
int Matrix::numRows() const { return mNumRows; }
int Matrix::numCols() const { return mNumCols; }
// Overloaded round bracket operator for one-based indexing
double& Matrix::operator()(int i, int j) {
    if (i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols){
        return mData[i - 1][j - 1];
    } else {
        cout << "Index out of bounds: (" << i << ", " << j << ")" << endl;
        return mData[0][0];
    }
    return mData[i - 1][j - 1];
}

// Overloaded assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        for (int i = 0; i < mNumRows; ++i) {
            delete[] mData[i];
        }
        delete[] mData;
        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; ++j) {
                mData[i][j] = other.mData[i][j];
            }
        }
    }
    return *this;
}

// Overloaded unary and binary operators for matrix operations
double Matrix::determinant() const {};

Matrix Matrix::inverse() const {};

Matrix Matrix::pseudoInverse() const {};

