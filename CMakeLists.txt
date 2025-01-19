cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem)

# Include directories
include_directories(include)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add JSON Library
find_package(nlohmann_json REQUIRED)

# Source files
set(SOURCES
    src/Book.cpp
    src/LibraryManager.cpp
)

# Test files
set(TESTS
    tests/BookTest.cpp
    tests/LibraryManagerTest.cpp
)

# Create executable for tests
add_executable(runBookTests ${SOURCES} ${TESTS})

# Create executable for main program
add_executable(library_management src/main.cpp src/Book.cpp src/LibraryManager.cpp)
target_link_libraries(library_management pthread nlohmann_json::nlohmann_json)

# Link Google Test and JSON libraries
target_link_libraries(runBookTests ${GTEST_LIBRARIES} pthread nlohmann_json::nlohmann_json)

# Enable testing
enable_testing()

# Add test command
add_test(NAME BookTests COMMAND runBookTests)
