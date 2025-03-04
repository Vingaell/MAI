cmake_minimum_required(VERSION 3.10)
project(OOP_lab_1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)


add_executable(main main.cpp fun.cpp)

enable_testing()
add_executable(tests tests.cpp fun.cpp)

target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)