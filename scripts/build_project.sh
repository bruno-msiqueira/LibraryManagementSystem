#!/bin/bash

# Script to automate the build and test process for the Library Management System.

# Variables
BUILD_DIR="build"
EXECUTABLE="runBookTests"

# Colors for messages
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

echo -e "${GREEN}Starting build process...${RESET}"

# Step 1: Clean or create the build directory
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning existing build directory..."
    rm -rf "$BUILD_DIR"
fi
mkdir "$BUILD_DIR"
cd "$BUILD_DIR" || exit

# Step 2: Generate build files with CMake
echo "Generating build files with CMake..."
if cmake ..; then
    echo -e "${GREEN}CMake configuration completed successfully.${RESET}"
else
    echo -e "${RED}CMake configuration failed.${RESET}"
    exit 1
fi

# Step 3: Compile the project
echo "Compiling the project..."
if make; then
    echo -e "${GREEN}Compilation completed successfully.${RESET}"
else
    echo -e "${RED}Compilation failed.${RESET}"
    exit 1
fi

# Step 4: Run tests
if [ -f "$EXECUTABLE" ]; then
    echo "Running tests..."
    if ./"$EXECUTABLE"; then
        echo -e "${GREEN}All tests passed successfully.${RESET}"
    else
        echo -e "${RED}Some tests failed. Check the output above for details.${RESET}"
        exit 1
    fi
else
    echo -e "${RED}Test executable not found: $EXECUTABLE.${RESET}"
    exit 1
fi

echo -e "${GREEN}Build process completed successfully.${RESET}"
