cmake_minimum_required(VERSION 3.24)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(Eigen3_INCLUDE_DIRS /usr/include/eigen3)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
add_executable(ex3 main.cpp)
target_link_libraries(ex3 ${OpenCV_LIBS})
