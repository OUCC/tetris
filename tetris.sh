#!/usr/bin/env bash
set -e

PREFIX32=${PREFIX32-"i686-pc-mingw32-"}
PREFIX64=${PREFIX64-"x86_64-pc-mingw32-"}

langs=(
    ""
    "-ch"
    "-jp"
)

defs=(
    "-DLANG_EN"
    "-DLANG_CH"
    "-DLANG_JP"
)

for i in {0..2} ; do
    echo "*** [IA-32] Compiling tetris.c..."
    ${PREFIX32}gcc "${defs[i]}" -Wall -O3 -c tetris.c

    echo "*** [IA-32] Compiling resource.rc..."
    ${PREFIX32}windres "${defs[i]}" resource.rc resource.o

    echo "*** [IA-32] Linking..."
    ${PREFIX32}gcc tetris.o resource.o -static -s -lcomctl32 -lgdi32 -lwinmm -mwindows -o "tetris-win-32${langs[i]}.exe"

    echo "*** [AMD64] Compiling tetris.c..."
    ${PREFIX64}gcc "${defs[i]}" -Wall -O3 -c tetris.c

    echo "*** [AMD64] Compiling resource.rc..."
    ${PREFIX64}windres "${defs[i]}" resource.rc resource.o

    echo "*** [AMD64] Linking..."
    ${PREFIX64}gcc tetris.o resource.o -static -s -lcomctl32 -lgdi32 -lwinmm -mwindows -o "tetris-win-64${langs[i]}.exe"

    rm -f tetris.o resource.o
done
