
#!/bin/bash

# Script to clean build and/or documentation directories

# Directories to clean
BUILD_DIR="build"
DOCS_DIR="docs"

# Parse command-line arguments
CLEAN_BUILD=false
CLEAN_DOCS=false

# Default behavior: clean everything if no arguments are provided
if [[ $# -eq 0 ]]; then
    CLEAN_BUILD=true
    CLEAN_DOCS=true
else
    while [[ $# -gt 0 ]]; do
        case $1 in
            --build)
                CLEAN_BUILD=true
                shift
                ;;
            --docs)
                CLEAN_DOCS=true
                shift
                ;;
            --all)
                CLEAN_BUILD=true
                CLEAN_DOCS=true
                shift
                ;;
            *)
                echo "[ERROR] Unknown option: $1"
                echo "Usage: $0 [--build] [--docs] [--all]"
                exit 1
                ;;
        esac
    done
fi

# Clean build directory
if [ "$CLEAN_BUILD" = true ]; then
    if [ -d "$BUILD_DIR" ]; then
        echo "Cleaning build directory..."
        rm -rf "$BUILD_DIR"
        echo "Build directory cleaned."
    else
        echo "Build directory does not exist. Skipping."
    fi
fi

# Clean documentation directory
if [ "$CLEAN_DOCS" = true ]; then
    if [ -d "$DOCS_DIR" ]; then
        echo "Cleaning documentation directory..."
        rm -rf "$DOCS_DIR"
        echo "Documentation directory cleaned."
    else
        echo "Documentation directory does not exist. Skipping."
    fi
fi

# Final message
echo "Cleanup completed."
