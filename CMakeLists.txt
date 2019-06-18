cmake_minimum_required(VERSION 3.14)
project(practice)

set(CMAKE_CXX_STANDARD 14)

add_library(ncurses Thermopylae/main.cpp )

add_executable(practice  Thermopylae/main.cpp Thermopylae/Person.cpp Thermopylae/Person.h Thermopylae/WorldObject.cpp Thermopylae/WorldObject.h Thermopylae/Spartan.h Thermopylae/Persian.h Thermopylae/Water.h Thermopylae/Rock.h Thermopylae/Nothing.h Thermopylae/vector2.h Thermopylae/Body.h)

target_link_libraries(practice -lncurses)

