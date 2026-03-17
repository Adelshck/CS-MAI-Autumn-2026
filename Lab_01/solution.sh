#!/bin/bash

show_help() {
    echo "Usage: $0 [OPTION]... [DIRECTORY]"
    echo "Search for all subdirectories within DIRECTORY and display their absolute paths."
    echo ""
    echo "Description:"
    echo "  This script performs a recursive depth-first search starting from the"
    echo "  given DIRECTORY. For every subdirectory found, it resolves the full"
    echo "  system path (absolute path) and prints it to the standard output."
    echo ""
    echo "Options:"
    echo "  -h, --help     display this help message and exit"
    echo ""
    echo "Examples:"
    echo "  $0 .              # Search in the current directory"
    echo "  $0 /home/user     # Search in a specific absolute path"
    echo ""
    echo "Exit status:"
    echo "  0  if OK,"
    echo "  1  if DIRECTORY is invalid or missing."
}

if [[ "$1" == "-h" || "$1" == "--help" ]]; then
    show_help
    exit 0
fi

if [ $# -eq 0 ]; then
    show_help
    exit 1
fi

TARGET_DIR=$1

if [ ! -d "$TARGET_DIR" ]; then
    show_help
    exit 1
fi

find "$TARGET_DIR" -type d | while read -r dir; do
    realpath "$dir"
done