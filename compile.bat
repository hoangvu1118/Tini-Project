@echo off
REM compile.bat - Simple compilation script

IF NOT EXIST "compile" mkdir compile

if "%1"=="main" (
    g++ -o compile/main src/main.cpp src/Matrix.cpp src/Vector.cpp src/LinearSystem.cpp -I./Header-Files
    echo Compiled main program
) else if "%1"=="vector" (
    g++ -o compile/test_vector tests/testVector.cpp src/Vector.cpp -I./Header-Files
    echo Compiled vector test
) else if "%1"=="matrix" (
    g++ -o compile/test_matrix tests/testMatrix.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
    echo Compiled matrix test
) else if "%1"=="linear" (
    g++ -o compile/test_linear tests/testLinear.cpp src/LinearSystem.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
    echo Compiled linear system test
) else if "%1"=="illposed" (
    g++ -o compile/test_illposed tests/testIllposed.cpp src/Matrix.cpp src/Vector.cpp src/LinearSystem.cpp -I./Header-Files
    echo Compiled ill-posed test
) else if "%1"=="pos-sym-lin-system"(
    g++ -o compile/test_pos_sym tests/testPosSymLinSystem.cpp src/PosSymLinSystem.cpp src/LinearSystem.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
    echo Compiled positive symmetric test
) else if "%1"=="matrix-vector" (
    g++ -o compile/test_matrix_vector tests/testMaVec.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
    echo Compiled matrix-vector multiplication test
) else (
    echo Usage: compile.bat [main^|vector^|matrix^|linear^|illposed^|matrix-vector]
)
