cmake_minimum_required(VERSION 3.9)
project(lab6)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab6 main.cpp bmp.cpp bmp.h objParser.cpp objParser.h intersect3D.cpp intersect3D.h octree.cpp octree.h geomerty.cpp geomerty.h rayTraycing.cpp rayTraycing.h main2.cpp)