# test/CMakeLists.txt

# Add GoogleTest
add_subdirectory(${PROJECT_SOURCE_DIR}/external/googletest googletest)

enable_testing()

# Include the source files from the main project, excluding main.cpp
file(GLOB PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")

# Add the test executable
add_executable(runTests test_main.cpp ${PROJECT_SOURCES})

# Link test executable against gtest and gtest_main
target_link_libraries(runTests gtest gtest_main)

# Include directories
target_include_directories(runTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
