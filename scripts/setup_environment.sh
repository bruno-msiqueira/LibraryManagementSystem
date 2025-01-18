#!/bin/bash

# Script to set up the development environment for the Library Management System project.

# Initialize status variables
status_gcc="not checked"
status_gdb="not checked"
status_make="not checked"
status_cmake="not checked"
status_gtest="not checked"
status_doxygen="not checked"
status_json="not checked"
status_vscode_extensions="not checked"

# List of VSCode extensions to install
vscode_extensions=(
    "ms-vscode.cpptools"              # C/C++ (Microsoft)
    "xaver.clang-format"              # Clang-Format (Xaver Hellauer)
    "formulahendry.code-runner"       # Code Runner (Jun Han)
    "cschlosser.doxdocgen"            # Doxygen Documentation Generator (Christoph Schlosser)
    "mhutchie.git-graph"              # Git Graph (mhutchie)
    "eamodio.gitlens"                 # GitLens (GitKraken)
    "davidschuldenfrei.gtest-adapter" # GoogleTest Adapter (David Schuldenfrei)
    "yzhang.markdown-all-in-one"      # Markdown All in One (Yu Zhang)
    "webfreak.debug"                  # Native Debug (WebFreak)
    "shardulm94.trailing-spaces"      # Trailing Spaces (Shardul Mahadik)
    "twxs.cmake"                      # CMake (twxs)
    "ms-vscode.cmake-tools"           # CMake Tools (Microsoft)
)

# Function to print the final report
print_report() {
    echo "-----------------------------------"
    echo "Setup Report:"
    echo "GCC: $status_gcc"
    echo "GDB: $status_gdb"
    echo "Make: $status_make"
    echo "CMake: $status_cmake"
    echo "Google Test: $status_gtest"
    echo "Doxygen: $status_doxygen"
    echo "JSON Library: $status_json"
    echo "VSCode Extensions:"
    # Print detailed status for each extension
    for extension in "${!extension_status[@]}"; do
        echo "  $extension: ${extension_status[$extension]}"
    done

    if [[ $status_gcc == "ok" && $status_gdb == "ok" && $status_make == "ok" && $status_cmake == "ok" && $status_gtest == "ok" && $status_doxygen == "ok" && $status_json == "ok" && $status_vscode_extensions == "ok" ]]; then
        echo "Environment setup completed successfully. The system is ready for use."
    else
        echo "Environment setup failed. Please review the errors above."
    fi
    echo "-----------------------------------"
}

# Step 1: Install GCC (compiler)
echo "Installing GCC..."
sudo apt update && sudo apt install -y build-essential
if gcc --version > /dev/null 2>&1; then
    status_gcc="ok"
else
    status_gcc="error"
fi

# Step 2: Install GDB (debugger)
echo "Installing GDB..."
sudo apt install -y gdb
if gdb --version > /dev/null 2>&1; then
    status_gdb="ok"
else
    status_gdb="error"
fi

# Step 3: Install Make
echo "Installing Make..."
sudo apt install -y make
if make --version > /dev/null 2>&1; then
    status_make="ok"
else
    status_make="error"
fi

# Step 4: Install CMake
echo "Installing CMake..."
sudo apt install -y cmake
if cmake --version > /dev/null 2>&1; then
    status_cmake="ok"
else
    status_cmake="error"
fi

# Step 5: Install Google Test
echo "Installing Google Test..."
sudo apt install -y libgtest-dev
cd /usr/src/gtest || exit
sudo rm -f lib/libgtest*.a
sudo rm -f /usr/lib/libgtest*.a
sudo cmake . && sudo make
sudo mv lib/libgtest*.a /usr/lib/
if [ -f /usr/lib/libgtest.a ] && [ -f /usr/lib/libgtest_main.a ]; then
    status_gtest="ok"
else
    status_gtest="error"
fi

# Step 6: Install Doxygen
echo "Installing Doxygen..."
sudo apt install -y doxygen
if doxygen --version > /dev/null 2>&1; then
    status_doxygen="ok"
else
    status_doxygen="error"
fi

# Step 7: Install JSON Library
echo "Installing JSON library..."
sudo apt install -y nlohmann-json3-dev
if [ -d /usr/include/nlohmann ]; then
    status_json="ok"
else
    status_json="error"
fi

# Step 8: Install VSCode Extensions
# VSCode extensions enhance the development experience.
echo "Installing VSCode extensions..."

# Dictionary to hold the status of each extension
declare -A extension_status

# Check if 'code' command is available
if ! command -v code &> /dev/null; then
    echo "[ERROR] VSCode is not installed or 'code' command is not available in PATH."
    status_vscode_extensions="error"
else
    for extension in "${vscode_extensions[@]}"; do
        echo "Installing extension: $extension..."
        if code --install-extension "$extension" --force > /dev/null 2>&1; then
            extension_status["$extension"]="ok"
        else
            extension_status["$extension"]="error"
        fi
    done

    # Verify installed extensions
    installed_extensions=$(code --list-extensions)
    for extension in "${vscode_extensions[@]}"; do
        if echo "$installed_extensions" | grep -q "$extension"; then
            extension_status["$extension"]="ok"
        else
            extension_status["$extension"]="error"
        fi
    done

    # Check overall status
    status_vscode_extensions="ok"
    for status in "${extension_status[@]}"; do
        if [ "$status" == "error" ]; then
            status_vscode_extensions="error"
            break
        fi
    done
fi

# Print final report
print_report
