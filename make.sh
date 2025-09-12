#!/bin/sh
set -e

cmd="${1:-build}"

if [ "$cmd" = "build" ]; then
    /usr/bin/clang -g src/arena/*.c src/router/*.c src/*.c -o main
fi

if [ "$cmd" = "run" ]; then
    ./main
fi
