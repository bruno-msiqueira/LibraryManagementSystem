#!/bin/bash

# Script to automate the build and test process for the Library Management System.

# Variables
BUILD_DIR="build"
EXECUTABLE="runBookTests"
CLEAN_BUILD=false

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        *)
            echo "[ERROR] Unknown option: $1"
            echo "Usage: $0 [--clean]"
            exit 1
            ;;
    esac
done

# Colors for messages
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

echo -e "${GREEN}Starting build process...${RESET}"

# Step 1: Clean or create the build directory
if [ "$CLEAN_BUILD" = true ]; then
    if [ -d "$BUILD_DIR" ]; then
        echo "Cleaning existing build directory..."
        rm -rf "$BUILD_DIR"
    fi
fi
mkdir "$BUILD_DIR"
cd "$BUILD_DIR" || exit

# Step 2: Generate build files with CMake
echo "Generating build files with CMake..."
if [ "$CLEAN_BUILD" = true ]; then
    if cmake ..; then
        echo -e "${GREEN}CMake configuration completed successfully.${RESET}"
    else
        echo -e "${RED}CMake configuration failed.${RESET}"
        exit 1
    fi
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
