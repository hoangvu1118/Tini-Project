#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"

// Function to solve ill-posed problems using pseudoinverse
Vector solvePseudoinverse(Matrix& A, Vector& b) {

    Matrix Aplus = A.pseudoInverse();

    int m = Aplus.numRows();
    int n = b.size();
    Vector x(m);
    
    for (int i = 1; i <= m; i++) {
        double sum = 0.0;
        for (int j = 1; j <= n; j++) {
            sum += Aplus(i, j) * b(j);
        }
        x(i) = sum;
    }
    
    return x;
}

struct DataPoint {
    double myct;
    double mmin;
    double mmax;
    double cach;
    double chmin;
    double chmax;
    double prp;  // Target variable
    double erp;  // Estimated performance (not used in regression)
    std::string vendor;
    std::string model;
};

std::vector<DataPoint> readDataset(const std::string& filename) {
    std::vector<DataPoint> dataset;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        DataPoint dp;
        std::string token;
        
        // Read vendor name and model
        std::getline(iss, dp.vendor, ',');
        std::getline(iss, dp.model, ',');
        
        // Read numerical attributes
        std::getline(iss, token, ','); 
        dp.myct = std::stod(token);
        std::getline(iss, token, ','); 
        dp.mmin = std::stod(token);
        std::getline(iss, token, ','); 
        dp.mmax = std::stod(token);
        std::getline(iss, token, ','); 
        dp.cach = std::stod(token);
        std::getline(iss, token, ','); 
        dp.chmin = std::stod(token);
        std::getline(iss, token, ','); 
        dp.chmax = std::stod(token);
        std::getline(iss, token, ','); 
        dp.prp = std::stod(token);
        std::getline(iss, token, ','); 
        dp.erp = std::stod(token);
        
        dataset.push_back(dp);
    }
    
    return dataset;
}


std::pair<std::vector<DataPoint>, std::vector<DataPoint>> trainTestSplit(
    const std::vector<DataPoint>& data, double trainRatio = 0.8) {
    
    // Create a copy of the data to shuffle
    std::vector<DataPoint> shuffledData = data;
    
    // Seed the random engine
    std::random_device rd;
    std::mt19937 g(rd());
    
    // Shuffle the data
    std::shuffle(shuffledData.begin(), shuffledData.end(), g);
    
    // Calculate split point
    size_t splitIdx = static_cast<size_t>(trainRatio * shuffledData.size());
    
    // Create training and testing sets
    std::vector<DataPoint> trainData(shuffledData.begin(), shuffledData.begin() + splitIdx);
    std::vector<DataPoint> testData(shuffledData.begin() + splitIdx, shuffledData.end());
    
    return {trainData, testData};
}

void setupLinearRegressionSystem(
    const std::vector<DataPoint>& trainData, 
    Matrix& A, 
    Vector& b) {
    
    int n = trainData.size();
    A = Matrix(n, 6);  // 6 predictive features
    b = Vector(n);     // Target values
    
    // Fill the coefficient matrix and target vector
    for (int i = 0; i < n; ++i) {
        // Note: Using 1-based indexing for Matrix and Vector
        A(i+1, 1) = trainData[i].myct;
        A(i+1, 2) = trainData[i].mmin;
        A(i+1, 3) = trainData[i].mmax;
        A(i+1, 4) = trainData[i].cach;
        A(i+1, 5) = trainData[i].chmin;
        A(i+1, 6) = trainData[i].chmax;
        
        b(i+1) = trainData[i].prp;
    }
}

Vector solveLinearRegression(Matrix& A,  Vector& b) {
    // Use the Moore-Penrose pseudoinverse for the overdetermined system
    return solvePseudoinverse(A, b);
}

double calculateRMSE(
    const std::vector<DataPoint>& testData, 
    Vector& coefficients) {
    
    double sumSquaredError = 0.0;
    int n = testData.size();
    
    for (int i = 0; i < n; ++i) {
        // Calculate predicted value using the model:
        // PRP = x1*MYCT + x2*MMIN + x3*MMAX + x4*CACH + x5*CHMIN + x6*CHMAX
        double predicted = 
            coefficients(1) * testData[i].myct + 
            coefficients(2) * testData[i].mmin +
            coefficients(3) * testData[i].mmax +
            coefficients(4) * testData[i].cach +
            coefficients(5) * testData[i].chmin +
            coefficients(6) * testData[i].chmax;
        
        // Actual value
        double actual = testData[i].prp;
        
        // Sum of squared errors
        sumSquaredError += (predicted - actual) * (predicted - actual);
    }
    
    // Calculate RMSE
    return std::sqrt(sumSquaredError / n);
}

void normalizeData(std::vector<DataPoint>& trainData, std::vector<DataPoint>& testData) {
    // Calculate mean and standard deviation for each feature from training data
    double myct_mean = 0, mmin_mean = 0, mmax_mean = 0, cach_mean = 0, chmin_mean = 0, chmax_mean = 0;
    double myct_std = 0, mmin_std = 0, mmax_std = 0, cach_std = 0, chmin_std = 0, chmax_std = 0;
    
    // Calculate means
    for (const auto& dp : trainData) {
        myct_mean += dp.myct;
        mmin_mean += dp.mmin;
        mmax_mean += dp.mmax;
        cach_mean += dp.cach;
        chmin_mean += dp.chmin;
        chmax_mean += dp.chmax;
    }
    
    int n = trainData.size();
    myct_mean /= n;
    mmin_mean /= n;
    mmax_mean /= n;
    cach_mean /= n;
    chmin_mean /= n;
    chmax_mean /= n;
    
    // Calculate standard deviations
    for (const auto& dp : trainData) {
        myct_std += (dp.myct - myct_mean) * (dp.myct - myct_mean);
        mmin_std += (dp.mmin - mmin_mean) * (dp.mmin - mmin_mean);
        mmax_std += (dp.mmax - mmax_mean) * (dp.mmax - mmax_mean);
        cach_std += (dp.cach - cach_mean) * (dp.cach - cach_mean);
        chmin_std += (dp.chmin - chmin_mean) * (dp.chmin - chmin_mean);
        chmax_std += (dp.chmax - chmax_mean) * (dp.chmax - chmax_mean);
    }
    
    myct_std = std::sqrt(myct_std / n);
    mmin_std = std::sqrt(mmin_std / n);
    mmax_std = std::sqrt(mmax_std / n);
    cach_std = std::sqrt(cach_std / n);
    chmin_std = std::sqrt(chmin_std / n);
    chmax_std = std::sqrt(chmax_std / n);
    
    // Normalize training data
    for (auto& dp : trainData) {
        dp.myct = (dp.myct - myct_mean) / myct_std;
        dp.mmin = (dp.mmin - mmin_mean) / mmin_std;
        dp.mmax = (dp.mmax - mmax_mean) / mmax_std;
        dp.cach = (dp.cach - cach_mean) / cach_std;
        dp.chmin = (dp.chmin - chmin_mean) / chmin_std;
        dp.chmax = (dp.chmax - chmax_mean) / chmax_std;
    }
    
    // Normalize test data using training statistics
    for (auto& dp : testData) {
        dp.myct = (dp.myct - myct_mean) / myct_std;
        dp.mmin = (dp.mmin - mmin_mean) / mmin_std;
        dp.mmax = (dp.mmax - mmax_mean) / mmax_std;
        dp.cach = (dp.cach - cach_mean) / cach_std;
        dp.chmin = (dp.chmin - chmin_mean) / chmin_std;
        dp.chmax = (dp.chmax - chmax_mean) / chmax_std;
    }
}

int main() {
    try {
        // Read the dataset
        std::string filename = "dataset/machine.data";
        std::vector<DataPoint> data = readDataset(filename);
        
        std::cout << "Dataset loaded: " << data.size() << " instances\n";
        
        // Split into training and testing sets
        auto [trainData, testData] = trainTestSplit(data);
        std::cout << "Training set: " << trainData.size() << " instances\n";
        std::cout << "Testing set: " << testData.size() << " instances\n";
        
        // Optional: Normalize the data
        normalizeData(trainData, testData);
        
        // Set up linear regression system
        Matrix A(trainData.size(), 6);  // Initialize with proper dimensions
        Vector b(trainData.size());     // Initialize with proper dimensions
        setupLinearRegressionSystem(trainData, A, b);
        
        // Solve the system to find the regression coefficients
        Vector coefficients = solveLinearRegression(A, b);
        
        // Display the coefficients
        std::cout << "\nLinear regression model: PRP = ";
        std::cout << coefficients(1) << "*MYCT + ";
        std::cout << coefficients(2) << "*MMIN + ";
        std::cout << coefficients(3) << "*MMAX + ";
        std::cout << coefficients(4) << "*CACH + ";
        std::cout << coefficients(5) << "*CHMIN + ";
        std::cout << coefficients(6) << "*CHMAX\n";
        
        // Evaluate the model on the test set
        double rmse = calculateRMSE(testData, coefficients);
        std::cout << "RMSE on test set: " << rmse << "\n";
        
        // Compare with the ERP (estimated relative performance) from the original article
        double erpRMSE = 0.0;
        for (const auto& dp : testData) {
            erpRMSE += (dp.erp - dp.prp) * (dp.erp - dp.prp);
        }
        erpRMSE = std::sqrt(erpRMSE / testData.size());
        std::cout << "Original article's ERP RMSE: " << erpRMSE << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
