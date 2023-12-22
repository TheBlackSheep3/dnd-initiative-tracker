cmake_minimum_required(VERSION 3.10)

project(dnd-initiative-tracker VERSION 0.1)

configure_file(src/cmake_variables.hpp.in cmake_variables.hpp)

add_executable(dnd-initiative-tracker src/main.cpp)
target_include_directories(dnd-initiative-tracker PUBLIC "${PROJECT_BINARY_DIR}")
