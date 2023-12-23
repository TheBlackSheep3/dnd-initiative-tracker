cmake_minimum_required(VERSION 3.10)

project(dnd-initiative-tracker VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(src/cmake_variables.hpp.in cmake_variables.hpp)

add_executable(dnd-initiative-tracker src/main.cpp src/entity.cpp src/encounter.cpp)
target_include_directories(dnd-initiative-tracker PUBLIC "${PROJECT_BINARY_DIR}")
