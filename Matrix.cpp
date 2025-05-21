#include "Header-Files/Matrix.h"
#include <cassert>
#include <iostream>
#include <cmath>

const double threshold = 1e-9;

Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    assert(mNumRows > 0 && mNumCols > 0);
    mData = new double*[mNumRows]; // Creates an array where each element is a pointer to a double.
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols]; // allocate memory for number of columns in each row
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = other.mData[i][j]; // assigning the value into matrix(copy)
        }
    }
}

Matrix::Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {
    mData = new double*[mNumRows]; 
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols](); // initialize to zero --> double[...]() --> 0.0
    }
}


Matrix::~Matrix() {
    if (mData != nullptr) {
        for (int i = 0; i < mNumRows; ++i) {
            delete[] mData[i];
        }
        delete[] mData;
        mData = nullptr;
    }
}

int Matrix::numRows() const { 
    return mNumRows; 
}

int Matrix::numCols() const { 
    return mNumCols; 
}


double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

double Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        if (mNumRows != other.mNumRows || mNumCols != other.mNumCols) {
            for (int i = 0; i < mNumRows; ++i) {
                delete[] mData[i];
            }
            delete[] mData;
            
            mNumRows = other.mNumRows;
            mNumCols = other.mNumCols;
            mData = new double*[mNumRows];
            for (int i = 0; i < mNumRows; ++i) {
                mData[i] = new double[mNumCols];
            }
        }

        for (int i = 0; i < mNumRows; ++i) {
            for (int j = 0; j < mNumCols; ++j) {
                mData[i][j] = other.mData[i][j];
            }
        }
    }
    return *this;
}

Matrix Matrix::operator+() const { 
    return *this;
}

Matrix Matrix::operator-() const { 
    Matrix result(*this);
    for (int i = 1; i <= mNumRows; i++) {
        for (int j = 1; j <= mNumCols; j++) {
            result(i, j) = -result(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const{
    assert(other.mNumRows == mNumRows && other.mNumCols == mNumCols);
    Matrix newMatrix(mNumRows, mNumCols);
    
    for(int i = 1; i <= mNumRows; i++) {
        for(int j = 1; j <= mNumCols; j++) {
            newMatrix(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return newMatrix;
}

Matrix Matrix::operator-(const Matrix& other) const{  
    assert(other.mNumRows == mNumRows && other.mNumCols == mNumCols);
    Matrix newMatrix(mNumRows, mNumCols);
    
    for(int i = 1; i <= mNumRows; i++) {
        for(int j = 1; j <= mNumCols; j++) {
            newMatrix(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return newMatrix;
}

Matrix Matrix::operator*(const Matrix& other) const { 
    assert(mNumCols == other.mNumRows);
    Matrix newMatrix(mNumRows, other.mNumCols);

    for(int i = 1; i <= mNumRows; i++) {
        for(int j = 1; j <= other.mNumCols; j++) {
            double temp = 0.0;
            for(int k = 1; k <= mNumCols; k++) {
                temp += (*this)(i, k) * other(k, j);
            }
            newMatrix(i, j) = temp;
        }
    }   
    return newMatrix;
}

Matrix Matrix::operator*(double scalar) const {  
    Matrix result(*this);
    for(int i = 1; i <= mNumRows; i++) {
        for(int j = 1; j <= mNumCols; j++) {
            result(i, j) *= scalar;
        }
    }
    return result;
}

double Matrix::determinant() const {
    assert(mNumCols == mNumRows);
    int n = mNumCols;
    
    double** matrix = new double*[n];
    for(int i = 0; i < n; i++) {
        matrix[i] = new double[n];
        for(int j = 0; j < n; j++) {
            matrix[i][j] = mData[i][j];
        }
    }

    int swapCount = 0;
    for (int i = 0; i < n; ++i) {
        int pivotRow = i;
        
        // Find the maximum element in the current column
        for (int j = i + 1; j < n; ++j) {
            if (fabs(matrix[j][i]) > fabs(matrix[pivotRow][i])) {
                pivotRow = j;
            }
        }

        if (fabs(matrix[pivotRow][i]) < threshold) {
            for(int k = 0; k < n; k++) {
                delete[] matrix[k];
            }
            delete[] matrix;
            return 0;
        }

        // Swap rows if necessary
        if (i != pivotRow) {
            for(int k = 0; k < n; k++) {
                double temp = matrix[i][k];
                matrix[i][k] = matrix[pivotRow][k];
                matrix[pivotRow][k] = temp;
            }
            swapCount++;
        }

        // Gaussian elimination
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    // Calculate determinant
    double det = (swapCount % 2 == 0) ? 1 : -1;
    for (int i = 0; i < n; ++i) {
        det *= matrix[i][i];
    }

    for(int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return det;
}


Matrix Matrix::inverse() const {
    assert(mNumCols == mNumRows);
    int n = mNumRows;
    
    // Check if matrix is invertible
    if (fabs(determinant()) < threshold) {
        std::cout << "Matrix is not invertible";
        assert(abs(determinant()) < threshold);
    }

    Matrix augmented(n, 2*n);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            augmented(i+1,j+1) = mData[i][j];
        }
        augmented(i+1,i+n+1) = 1.0;
    }

    // Gauss-Jordan elimination
    for(int i = 0; i < n; i++) {
        int pivotRow = i;
        for(int j = i + 1; j < n; j++) {
            if(fabs(augmented(j+1,i+1)) > fabs(augmented(pivotRow+1,i+1))) {
                pivotRow = j;
            }
        }

        if(pivotRow != i) {
            for(int j = 0; j < 2*n; j++) {
                double temp = augmented(i+1,j+1);
                augmented(i+1,j+1) = augmented(pivotRow+1,j+1);
                augmented(pivotRow+1,j+1) = temp;
            }
        }

        double pivot = augmented(i+1,i+1);
        for(int j = 0; j < 2*n; j++) {
            augmented(i+1,j+1) /= pivot;
        }

        // Eliminate column
        for(int j = 0; j < n; j++) {
            if(j != i) {
                double factor = augmented(j+1,i+1);
                for(int k = 0; k < 2*n; k++) {
                    augmented(j+1,k+1) -= factor * augmented(i+1,k+1);
                }
            }
        }
    }

    Matrix inverse(n, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            inverse(i+1,j+1) = augmented(i+1,j+n+1);
        }
    }

    return inverse;
}

Matrix Matrix::pseudoInverse() const {
   
    Matrix transpose(mNumCols, mNumRows);
    // Create transpose
    for(int i = 0; i < mNumRows; i++) {
        for(int j = 0; j < mNumCols; j++) {
            transpose(j+1,i+1) = mData[i][j];
        }
    }

    if(mNumRows < mNumCols) {
        // A⁺ = Aᵀ(AAᵀ)⁻¹
        Matrix AAT = (*this) * transpose;
        Matrix AATInv = AAT.inverse();
        return transpose * AATInv;
    } else {
        // A⁺ = (AᵀA)⁻¹Aᵀ
        Matrix ATA = transpose * (*this);
        Matrix ATAInv = ATA.inverse();
        return ATAInv * transpose;
    }
}