cmake_minimum_required(VERSION 3.15)
project(MatrixCircuitSolver VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enforce professional, zero-tolerance warning rules across compilers
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

include_directories(include)

add_executable(circuit_solver 
    src/main.cpp 
    src/matrix_solver.cpp 
    src/circuit.cpp
)
