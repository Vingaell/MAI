cmake_minimum_required(VERSION 3.10)

# Укажите название проекта и стандарт C++
project(main)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл и указываем все исходные файлы
add_executable(main
    src/main.cpp
    src/Scene.cpp
    src/ray.hpp
    src/Scene.hpp
    src/camera/Camera.hpp
    src/shapes/Plane.hpp
    src/shapes/Shape.hpp
    src/shapes/Sphere.hpp
)

# Указываем директории для поиска заголовочных файлов
target_include_directories(main PRIVATE
    src
    src/camera
    src/shapes
)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Настраиваем дополнительные опции компиляции
target_compile_options(main PRIVATE -Wall -Wextra -pedantic)

# Связываем с библиотеками OpenGL и GLEW
target_link_libraries(main
    OpenGL::GL 
    GLEW::GLEW
    GLU 
    sfml-system 
    sfml-window 
    sfml-graphics
)

