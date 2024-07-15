cmake_minimum_required(VERSION 3.10)
project(DataProcessor)

set(CMAKE_CXX_STANDARD 20)

# Add include directories
include_directories(include)

# Add source files, excluding main.cpp
file(GLOB SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")

# Define the main executable
add_executable(DataProcessor ${SOURCES} src/main.cpp)

# Add subdirectory for tests
add_subdirectory(tests)
