#!/bin/bash

# Script to automate the generation of Doxygen documentation.

# Variables
DOXYFILE="Doxyfile"
DOCS_OUTPUT_DIR="docs"

# Check if Doxyfile exists
if [ ! -f "$DOXYFILE" ]; then
    echo "[ERROR] Doxyfile not found in the current directory."
    exit 1
fi

# Clean up the docs directory
if [ -d "$DOCS_OUTPUT_DIR" ]; then
    echo "Cleaning up existing documentation..."
    rm -rf "$DOCS_OUTPUT_DIR"
fi

# Generate documentation
echo "Generating documentation with Doxygen..."
doxygen "$DOXYFILE"

# Check if documentation was generated successfully
if [ -d "$DOCS_OUTPUT_DIR/html" ]; then
    echo "Documentation generated successfully in '$DOCS_OUTPUT_DIR'."
else
    echo "[ERROR] Documentation generation failed."
    exit 1
fi
