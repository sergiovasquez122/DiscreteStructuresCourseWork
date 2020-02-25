cmake_minimum_required(VERSION 3.12)
project(matrix_calculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(matrix_calculator main.cpp Fraction.cpp Fraction.h Matrix.h)