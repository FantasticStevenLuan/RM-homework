cmake_minimum_required(VERSION 3.24)
project(ex2)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(Eigen3_INCLUDE_DIRS /usr/include/eigen3)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
add_executable(ex2 main.cpp)
target_link_libraries(ex2 ${OpenCV_LIBS})