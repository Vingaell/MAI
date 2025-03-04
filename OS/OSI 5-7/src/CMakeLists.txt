cmake_minimum_required(VERSION 3.0)
project(MyProgram)

find_package(PkgConfig REQUIRED)
pkg_search_module(ZeroMQ REQUIRED libzmq)

# Добавьте исполняемые файлы
add_executable(server Server.cpp ZMQFunctions.h)
add_executable(client Client.cpp ZMQFunctions.h)

# Целевые свойства для сервера
target_link_libraries(server PRIVATE ${ZeroMQ_LIBRARIES})
target_compile_options(server PRIVATE -fsanitize=address -w)

# Целевые свойства для клиента
target_link_libraries(client PRIVATE ${ZeroMQ_LIBRARIES})
target_compile_options(client PRIVATE -fsanitize=address -w)

# Удаление исполняемых файлов при вызове make clean
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P clean-all.cmake
)

# Генерация файла clean-all.cmake
file(WRITE clean-all.cmake "file(REMOVE server client)")


