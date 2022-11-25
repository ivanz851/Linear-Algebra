cmake_minimum_required(VERSION 3.23)
project(ClionProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(ClionProject main.cpp Matrix.h exceptions.h exceptions.cpp Vector.h Vector.cpp EquationSystem.h Rational.h Rational.cpp Poly.cpp Poly.h BigInt.cpp BigInt.h)
