Snake GL

Установка необходимых библиотек
$ sudo apt-get update
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
подробнее: http://www.codebind.com/linux-tutorials/install-opengl-ubuntu-linux/

Для CLion добавить в CMakeLists.txt
target_link_libraries(${PROJECT_NAME} -lglut -lGLU -lGL)

Найденные альтернативные настройки не работают, при запуске программа рисует только черный экран:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglut -lGLU -lGL ")
set(CMAKE_CXX_STANDARD 17)
add_executable(snakeog main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
