#!/bin/bash

# Script to verify and create the folder structure for the Library Management System project.

# Define the folder structure
folders=(
    "include"      # Header files
    "src"          # Source files
    "tests"        # Unit tests
    "scripts"      # Scripts for setup or utilities
    ".vscode"      # VSCode settings
)

# Function to create folders if they don't exist
create_folders() {
    all_ok=true
    for folder in "${folders[@]}"; do
        if [ -d "$folder" ]; then
            echo "[OK] Folder '$folder' already exists."
        else
            mkdir -p "$folder"
            if [ $? -eq 0 ]; then
                echo "[CREATED] Folder '$folder' was created."
            else
                echo "[ERROR] Failed to create folder '$folder'."
                all_ok=false
            fi
        fi
    done

    # Final status message
    if [ "$all_ok" = true ]; then
        echo "Folder structure setup complete. All folders are OK."
    else
        echo "Folder structure setup incomplete. Please check the errors above."
    fi
}

# Execute the function
echo "Verifying and creating project folder structure..."
create_folders
