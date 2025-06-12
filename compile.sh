#!/bin/bash
# filepath: /mnt/d/Coding_Projects/CeePlus/Tini-Project/compile.sh

mkdir -p compile

case "$1" in
    "main")
        g++ -o compile/main src/main.cpp src/Matrix.cpp src/Vector.cpp src/LinearSystem.cpp -I./Header-Files
        echo "Compiled main program"
        ;;
    "vector")
        g++ -o compile/test_vector tests/testVector.cpp src/Vector.cpp -I./Header-Files
        echo "Compiled vector test"
        ;;
    "matrix")
        g++ -o compile/test_matrix tests/testMatrix.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
        echo "Compiled matrix test"
        ;;
    "linear")
        g++ -o compile/test_linear tests/testLinear.cpp src/LinearSystem.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
        echo "Compiled linear system test"
        ;;
    "illposed")
        g++ -o compile/test_illposed tests/testIllposed.cpp src/Matrix.cpp src/Vector.cpp src/LinearSystem.cpp -I./Header-Files
        echo "Compiled ill-posed test"
        ;;
    "pos-sym-lin-system")
        g++ -o compile/test_pos_sym tests/testPosSymLinSystem.cpp src/PosSymLinSystem.cpp src/LinearSystem.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
        echo "Compiled positive symmetric test"
        ;;
    "matrix-vector")
        g++ -o compile/test_matrix_vector tests/testMaVec.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
        echo "Compiled matrix-vector multiplication test"
        ;;
    "regression")
        g++ -o compile/cpu_regression src/cpuRegression.cpp src/Matrix.cpp src/Vector.cpp src/LinearSystem.cpp -I./Header-Files
        echo "Compiled CPU regression analysis"
        ;;
    *)
        echo "Usage: ./compile.sh [main|vector|matrix|linear|illposed|pos-sym-lin-system|matrix-vector|regression]"
        ;;
esac