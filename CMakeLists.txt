cmake_minimum_required(VERSION 3.10)
project(LibraryManagementSystem)

# Enable testing
enable_testing()

# Include directories
include_directories(include)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Source files for the Book class
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

# Link Google Test libraries
target_link_libraries(runBookTests ${GTEST_LIBRARIES} pthread)

# Add test command
add_test(NAME BookTests COMMAND runBookTests)
