cmake_minimum_required(VERSION 3.10)
project(ex3_2)


set(CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ex3_2 main.cpp)

target_link_libraries(ex3_2 ${OpenCV_LIBS}  )

