configure_file(cmake_variables.hpp.in cmake_variables.hpp)

add_executable(dnd-initiative-tracker main.cpp entity.cpp encounter.cpp)
target_link_libraries(dnd-initiative-tracker dnd-initiative-tracker_compiler_options)
target_include_directories(dnd-initiative-tracker PUBLIC "${PROJECT_BINARY_DIR}/src")
