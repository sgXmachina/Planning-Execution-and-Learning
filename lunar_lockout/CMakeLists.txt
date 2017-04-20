cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project (lunar_lockout)
include_directories(include)
include_directories(src)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# Create the executable for running the lunar lockout puzzle.
add_executable(lunar_lockout_runner
                lunar_lockout_runner.cpp
                ${SOURCES}
                ${HEADERS})