#!/usr/bin/env bash
set -e

PREFIX=${PREFIX-"arm-mingw32ce-"}

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
    echo "*** Compiling tetris.c..."
    ${PREFIX}gcc "${defs[i]}" -Wall -O3 -march=armv5tej -mcpu=arm926ej-s -c tetris.c

    echo "*** Compiling resource.rc..."
    ${PREFIX}windres "${defs[i]}" resource.rc resource.o

    echo "*** Linking..."
    ${PREFIX}gcc tetris.o resource.o -static -s -lcommctrl -lcommdlg -lmmtimer -o "tetris-wce-armv5tej${langs[i]}.exe"

    rm -f tetris.o resource.o
done

echo "OK"
