#!/bin/bash
cmake --build build
cd build
TARGET="$1"

if [[ -z "$TARGET" ]]; then
    echo "Usage: $0 <file>"
    exit 1
fi

if [[ -x "$TARGET" ]]; then
    ./"$TARGET"
else

    echo "File not executable or not found: $TARGET"
fi
