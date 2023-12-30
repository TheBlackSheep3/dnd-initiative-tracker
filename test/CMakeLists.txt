include(FetchContent)
# fetch version 1.14.0 of GoogleTest from GitHub
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(entity_test entity_test.cpp)
target_link_libraries(
	entity_test
	dnd-initiative-tracker_compiler_options
	entity
	GTest::gtest_main
)
target_include_directories(entity_test PRIVATE "${PROJECT_SOURCE_DIR}/src")

add_executable(encounter_test encounter_test.cpp)
target_link_libraries(
	encounter_test
	dnd-initiative-tracker_compiler_options
	encounter
	entity
	GTest::gtest_main
)
target_include_directories(encounter_test PRIVATE "${PROJECT_SOURCE_DIR}/src")

include(GoogleTest)
gtest_discover_tests(entity_test)
gtest_discover_tests(encounter_test)
