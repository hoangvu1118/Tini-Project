How to run test 
### Matrix
```
compile.bat matrix
```
This will compile tests/testMatrix.cpp into compile/test_matrix.exe

### Vector
```
compile.bat vector
```

### Linear System
```
g++ -o test_linear_system tests/LinearSystemTest.cpp src/LinearSystem.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
```
### Main
```
g++ -o compile/main src/main.cpp src/Matrix.cpp src/Vector.cpp src/LinearSystem.cpp -I./Header-Files
```
