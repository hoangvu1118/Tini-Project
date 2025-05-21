# pragma once

#include <cassert>
#include <iostream>

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    // Constructor
    Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {
        assert(numRows > 0 && numCols > 0);
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols]();
        }
    }

    // Copy Constructor
    Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; ++j) {
                mData[i][j] = other.mData[i][j];
            }
        }
    }

    // Destructor
    ~Matrix() {
        for (int i = 0; i < mNumRows; ++i) {
            delete[] mData[i];
        }
        delete[] mData;
    }

    // Accessors
    int numRows() const { return mNumRows; }
    int numCols() const { return mNumCols; }

    // Overloaded round bracket operator for one-based indexing
    double& operator()(int i, int j) {
        assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
        return mData[i - 1][j - 1];
    }

    // Overloaded assignment operator
    Matrix& operator=(const Matrix& other) {
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

    double determinant() const;

    Matrix inverse() const;

    Matrix pseudoInverse() const;
};
