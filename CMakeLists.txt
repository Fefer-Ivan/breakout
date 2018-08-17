cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Wold-style-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wsign-conversion -Wunreachable-code -Wno-missing-braces")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fno-stack-protector")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB SOURCES "*.cpp")
list(REMOVE_ITEM SOURCES main.cpp)
add_library(breakout_lib ${SOURCES})

add_executable(breakout main.cpp)
target_link_libraries(breakout breakout_lib)

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(breakout_tests ${TEST_SOURCES})
target_link_libraries(breakout_tests breakout_lib gtest)
target_include_directories(breakout_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
