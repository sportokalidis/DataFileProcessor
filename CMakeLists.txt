cmake_minimum_required(VERSION 3.10)
project(DataProcessor)

set(CMAKE_CXX_STANDARD 11)

# Add include directories
include_directories(include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Define the executable
add_executable(DataProcessor ${SOURCES})