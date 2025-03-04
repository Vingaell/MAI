cmake_minimum_required(VERSION 3.10)
project(OOP6)

include_directories(${GTEST_INCLUDE_DIRS})
add_subdirectory(googletest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp observer.cpp factory.cpp NPC.cpp ork.cpp bear.cpp squirrel.cpp)

add_executable(tests tests.cpp observer.cpp factory.cpp NPC.cpp ork.cpp bear.cpp squirrel.cpp)

target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
