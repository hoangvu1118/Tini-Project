# C++ Linear Algebra and CPU Regression Project

## 1. How to Compile

The `compile.bat` script is used to compile the different parts of the project. Compiled executables are placed in the `compile/` directory.

### General Usage

```Bash
compile.bat <component_name>
```

### Matrix

```Bash
compile.bat matrix
```

This will compile `tests/testMatrix.cpp` into `compile/test_matrix.exe`.

### Vector

```Bash
compile.bat vector
```

### Linear System

```Bash
compile.bat linear
```

This will compile tests/testLinear.cpp into `compile/test_linear.exe`.

### `compile.bat` illposed

```Bash
compile.bat illposed
```

To run each test, run the executable individually for each class:

```Bash
compile\test_vector.exe
compile\test_matrix.exe
compile\test_linear.exe
compile\test_illposed.exe
```

## 2. Creating new cpp files

Put the following into `compile.bat`:

```Bash
else if "%1"=="mynewfile" (
    g++ -o compile/mynewfile src/mynewfile.cpp src/Matrix.cpp src/Vector.cpp -I./Header-Files
    echo Compiled mynewfile
)
```

> [!NOTE]
> Remember to change the name of the files.

Then run:

```Bash
compile.bat mynewfile
```
