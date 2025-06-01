## C++ Linear Algebra and CPU Regression Project 🚀
### How to Compile ⚙️
The compile.bat script is used to compile the different parts of the project. Compiled executables are placed in the compile/ directory.
#### General Usage:
```
compile.bat <component_name>
```
#### Matrix
```
compile.bat matrix
```
This will compile tests/testMatrix.cpp into compile/test_matrix.exe

#### Vector
```
compile.bat vector
```

#### Linear System
```
compile.bat linear
```
This will compile tests/testLinear.cpp into compile/test_linear.exe

#### compile.bat illposed
```
compile.bat illposed
```

To run each test - Run the executable individually for each class
```
compile\test_vector.exe
compile\test_matrix.exe
compile\test_linear.exe
compile\test_illposed.exe
```

## To create new cpp files
```
else if "%1"=="mynewfile" (
    g++ -o compile/mynewfile src/mynewfile.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
    echo Compiled mynewfile
)
```
Put this in the `compile.bat`, remember to change the name of the files 
Then run 
```
compile.bat mynewfile
```


