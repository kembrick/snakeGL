Snake
Выполнена на основе кода (с) FamTrinli https://www.youtube.com/watch?v=cEWNPLtBTAM 

Установка необходимых библиотек
$ sudo apt-get update
$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
подробнее: http://www.codebind.com/linux-tutorials/install-opengl-ubuntu-linux/

Для CLion добавить в CMakeLists.txt
target_link_libraries(${PROJECT_NAME} -lglut -lGLU -lGL)

Нагугленные альтернативные настройки не работают, с ними при запуске программа выдает только черный экран, приводятся только  для справки:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglut -lGLU -lGL ")
set(CMAKE_CXX_STANDARD 17)
add_executable(snakeog main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

Планы по изменению приложения:
1. Исправить некоторые ошибки, например, сейачас корм может появляться на тушке змеи.
2. Реализовать более классический вариант игры: нельзя врезаться в стенки и переезжать себя, корм только один на поле, змея ускоряется по мере роста. Можно предлагать выбор версии перед началом игры. Например, еще одна модификация - с добавлением препятствий на поле.
3. Сделать запись в таблицу рекордов (в текостовый файл).
4. Заменить примитивы на более продвинутую графику.
