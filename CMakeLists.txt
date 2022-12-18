cmake_minimum_required(VERSION 3.20)
project(bezierTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "--pedantic-errors -Wall")

add_executable(${PROJECT_NAME} code/main.cpp code/Vector.cpp code/Vector.hpp code/SingleQBezier.cpp code/SingleQBezier.hpp code/Bezier.hpp code/Bezier.cpp code/BezierChain.cpp code/BezierChain.hpp)

target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-window sfml-system)
