# pragma once

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem {
public:
    PosSymLinSystem(Matrix* A, Vector* b);
    virtual ~PosSymLinSystem();

    virtual Vector Solve() override;

private:
    bool isSymmetric(const Matrix& A);
};
