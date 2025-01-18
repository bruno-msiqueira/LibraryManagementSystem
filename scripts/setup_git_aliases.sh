#!/bin/bash

# This script will register Git-related aliases in the ~/.bash_aliases.

# Define the alias file (for bash, it's ~/.bash_aliases; change for zsh if needed)
ALIAS_FILE="$HOME/.bash_aliases"  # Change to "$HOME/.zsh_aliases" if using Zsh

# Check if the alias file exists, if not create it
if [ ! -f "$ALIAS_FILE" ]; then
    echo "$ALIAS_FILE does not exist. Creating a new one."
    touch "$ALIAS_FILE"
fi

# Check if the Git Aliases section already exists in the alias file, otherwise add a comment to note the section
if ! grep -q "# Custom Git Aliases" "$ALIAS_FILE"; then
    echo "# Custom Git Aliases" >> "$ALIAS_FILE"
    echo "Added Git Aliases section to $ALIAS_FILE"
fi

# Add or replace the aliases for the Git commands in the alias file
# Use grep to check for existence of alias and only add if it does not exist

# Register git aliases for prompt usage (will use 'git' as base command)
grep -q "alias gl=" "$ALIAS_FILE" || echo "alias gl='git log --decorate --pretty=\"%C(yellow)%h %C(cyan)%cd %Cblue%aN%C(auto)%d %Creset%s\" --abbrev-commit --date=format:\"%Y-%m-%d %H:%M\"'" >> "$ALIAS_FILE"
grep -q "alias glg=" "$ALIAS_FILE" || echo "alias glg='git log --decorate --pretty=\"%C(yellow)%h %C(cyan)%cd %Cblue%aN%C(auto)%d %Creset%s\" --abbrev-commit --date=format:\"%Y-%m-%d %H:%M\" --graph'" >> "$ALIAS_FILE"
grep -q "alias gsu=" "$ALIAS_FILE" || echo "alias gsu='git submodule update --init --recursive'" >> "$ALIAS_FILE"
grep -q "alias gupd=" "$ALIAS_FILE" || echo "alias gupd='git fetch && git pull && git submodule update --init --recursive'" >> "$ALIAS_FILE"

# Confirmation message
echo "Git-related aliases have been registered successfully!"

# Optional: Display the updated alias file for verification
echo "Updated $ALIAS_FILE:"
cat "$ALIAS_FILE"

#Display the updated alias file and bashrc/zshrc for verification
echo "Updated $ALIAS_FILE:"
cat "$ALIAS_FILE"
