cmake_minimum_required(VERSION 3.10)
project(ex3)


set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex3 main.cpp)

target_link_libraries(ex3 ${OpenCV_LIBS}  )

