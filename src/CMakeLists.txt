configure_file(cmake_variables.hpp.in cmake_variables.hpp)

add_library(entity entity.cpp)
target_link_libraries(entity PUBLIC
	dnd-initiative-tracker_compiler_options
)

add_library(encounter encounter.cpp)
target_link_libraries(encounter PUBLIC
	dnd-initiative-tracker_compiler_options
	entity
)

add_executable(dnd-initiative-tracker main.cpp)
target_link_libraries(dnd-initiative-tracker PUBLIC
	dnd-initiative-tracker_compiler_options
	encounter
)
target_include_directories(dnd-initiative-tracker PUBLIC "${PROJECT_BINARY_DIR}/src")
