cmake_minimum_required(VERSION 3.14)
project(Thermopylae)

set(CMAKE_CXX_STANDARD 14)

add_library(ncurses main.cpp )

add_executable(Thermopylae  main.cpp Person.cpp Person.h WorldObject.cpp WorldObject.h Spartan.h Persian.h Water.h Rock.h Nothing.h vector2.h Body.h)

target_link_libraries(Thermopylae -lncurses)

