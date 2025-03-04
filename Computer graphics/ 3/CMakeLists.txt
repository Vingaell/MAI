cmake_minimum_required(VERSION 3.10)

project(3D_Scene)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Путь к библиотекам SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(main main.cpp)

# Подключение библиотек SFML и OpenGL
target_link_libraries(main sfml-graphics sfml-window sfml-system GLU GL)




