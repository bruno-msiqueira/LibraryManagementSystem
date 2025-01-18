#!/bin/bash

# Script to automate the generation of Doxygen documentation, including PDF.

# Variables
DOXYFILE="Doxyfile"
DOCS_OUTPUT_DIR="docs"
LATEX_DIR="$DOCS_OUTPUT_DIR/latex"
PDF_FILE="Library_Management_System.pdf"

# Clean previous documentation
echo "Cleaning up existing documentation..."
rm -rf "$DOCS_OUTPUT_DIR"

# Check if Doxyfile exists
if [ ! -f "$DOXYFILE" ]; then
    echo "[ERROR] Doxyfile not found in the current directory."
    exit 1
fi

# Generate documentation
echo "Generating documentation with Doxygen..."
doxygen "$DOXYFILE"

# Check if LaTeX files were generated
if [ ! -d "$LATEX_DIR" ]; then
    echo "[ERROR] LaTeX files not generated. Check Doxygen configuration."
    exit 1
fi

echo "LaTeX files generated successfully."

# Compile PDF
echo "Compiling PDF documentation..."
cd "$LATEX_DIR" || exit
make > /dev/null 2>&1

if [ -f "refman.pdf" ]; then
    echo "PDF generated successfully."
    mkdir -p ../
    mv refman.pdf "../$PDF_FILE"
else
    echo "[ERROR] PDF generation failed. Check LaTeX logs for details."
    exit 1
fi

# Final message
echo "Documentation generation complete. PDF available at '$PDF_FILE'."
