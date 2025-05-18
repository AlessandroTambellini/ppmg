#!/bin/sh

set -xe
mkdir -p ./bin/

build() {
    if [ "$1" = "sdl" ]; then
        gcc -Wall -Wextra -DUSE_SDL -lSDL2 main.c ppmg.c -o ./bin/main
    else
        gcc -Wall -Wextra main.c ppmg.c -o ./bin/main
    fi
}

if [ "$1" = "sdl" ]; then
    build sdl
else
    build
fi
