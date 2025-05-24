# pragma once
#include <iostream>

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    // Constructor
    Matrix(int numRows, int numCols);

    // Copy Constructor
    Matrix(const Matrix& other);

    // Destructor
    ~Matrix();

    // Accessors
    int numRows() const;
    int numCols() const;

    // Overloaded round bracket operator for one-based indexing
    double& operator()(int i, int j);
    double operator()(int i, int j) const;

    // Overloaded assignment operator
    Matrix& operator=(const Matrix& other);


    Matrix operator+() const;

    Matrix operator-() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix operator*(double scalar) const;


    double determinant() const;

    Matrix inverse() const;

    Matrix pseudoInverse() const;

    Matrix transpose() const;
};
