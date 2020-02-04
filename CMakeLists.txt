cmake_minimum_required(VERSION 3.15)
project(snakeog)

set(CMAKE_CXX_STANDARD 17)

add_executable(snakeog main.cpp)

target_link_libraries(${PROJECT_NAME} -lglut -lGLU -lGL)