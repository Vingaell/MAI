cmake_minimum_required(VERSION 3.10)
project(LightingWithShaders)

cmake_policy(SET CMP0072 OLD) # Предпочтение старой реализации
find_package(OpenGL REQUIRED)

# Найти SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Указать стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавить исполняемый файл
add_executable(main main.cpp utils.cpp)

# Указать директории для заголовков
target_include_directories(main PRIVATE 
    ${OPENGL_INCLUDE_DIRS} 
    /usr/include
)

# Связывание библиотек
target_link_libraries(main
    OpenGL::GL 
    GLEW 
    GLU 
    sfml-system 
    sfml-window 
    sfml-graphics
)
