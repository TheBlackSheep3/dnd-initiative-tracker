cmake_minimum_required(VERSION 3.10)

project(dnd-initiative-tracker VERSION 0.1)
add_library(dnd-initiative-tracker_compiler_options INTERFACE)
set(PROJECT_DISPLAY_NAME "\"Dungeons & Dragons intiative tracker\"")
set(PROJECT_AUTHOR "\"Niklas Dießner\"")

target_compile_features(dnd-initiative-tracker_compiler_options INTERFACE cxx_std_17)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(dnd-initiative-tracker_compiler_options INTERFACE
	"$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wpedantic;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
	"$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

add_subdirectory(src)
add_subdirectory(test)
