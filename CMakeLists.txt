cmake_minimum_required(VERSION 3.20)
project(DeadlockFPS VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(deadlockfps src/camera_controller.cpp)
target_include_directories(deadlockfps PUBLIC include)

if(MSVC)
    target_compile_options(deadlockfps PRIVATE /W4 /permissive-)
else()
    target_compile_options(deadlockfps PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(deadlockfps_demo demo/main.cpp)
target_link_libraries(deadlockfps_demo PRIVATE deadlockfps)

enable_testing()
add_executable(deadlockfps_tests tests/camera_controller_tests.cpp)
target_link_libraries(deadlockfps_tests PRIVATE deadlockfps)
add_test(NAME deadlockfps_tests COMMAND deadlockfps_tests)
