cmake_minimum_required(VERSION 3.16)
project(AoC LANGUAGES CXX)

set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --stdlib=libc++")

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(SOURCES
	src/main.cpp
	src/logging.cpp

	src/day_1.cpp
	)

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")
add_compile_definitions(PROJECT_FOLDER="${CMAKE_SOURCE_DIR}")

add_executable(aoc ${SOURCES})
target_compile_features(aoc PUBLIC cxx_std_20)
