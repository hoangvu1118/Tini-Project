How to run test 
### Matrix
```
g++ -o matrix_program testMatrix.cpp Matrix.cpp -std=c++11 -I./Header-Files
```

### Vector
```
g++ -o test_vector tests/VectorTest.cpp src/Vector.cpp -I./Header-Files
```

### Linear System
```
g++ -o test_linear_system tests/LinearSystemTest.cpp src/LinearSystem.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
```
### Main
```
g++ -o compile/main src/main.cpp src/Matrix.cpp src/Vector.cpp src/LinearSystem.cpp -I./Header-Files
```
