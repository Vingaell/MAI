cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MySFMLApp)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Укажите путь к SFML (если установлен из пакетов)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Укажите исходные файлы
add_executable(main main.cpp)

# Свяжите SFML с проектом
target_link_libraries(main sfml-graphics sfml-window sfml-system)

