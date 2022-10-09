cmake_minimum_required(VERSION 3.23)
project(ClionProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(ClionProject main.cpp Matrix.h Matrix.cpp exceptions.h exceptions.cpp Problem_1.h Problem_1.cpp Vector.h Vector.cpp EquationSystem.h EquationSystem.cpp)
