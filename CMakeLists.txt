cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -Wold-style-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wsign-conversion -Wunreachable-code -Wno-missing-braces")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fno-stack-protector")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB LIB_SOURCES "*.cpp")
file(GLOB GAME_OBJECTS_SOURCES "game_objects/*.cpp")
add_library(breakout_lib ${LIB_SOURCES} ${GAME_OBJECTS_SOURCES})
target_link_libraries(breakout_lib pthread)

find_package(Qt5Widgets)

file(GLOB APP_SOURCES "app/*.cpp")
file(GLOB APP_UI "app/*.ui")
add_executable(breakout ${APP_SOURCES} ${APP_UI})
target_link_libraries(breakout breakout_lib Qt5::Widgets)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(breakout_tests ${TEST_SOURCES})
target_link_libraries(breakout_tests breakout_lib gtest)

add_test(NAME unit_tests COMMAND breakout_tests)
