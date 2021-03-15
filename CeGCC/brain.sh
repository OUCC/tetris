#!/usr/bin/env bash
set -e

if(test -e "resource_${1:-"EN"}.rc"); then # With Resource Script
    echo "*** Compiling and assembling the C source (tetris.c)..."
    if(test -e "tetris.c.o"); then
        rm -f "tetris.c.o"
    fi
    arm-mingw32ce-gcc -D LANG_${1:-"EN"} -Wall -O3 -march=armv5tej -mcpu=arm926ej-s -c tetris.c -o tetris.c.o
    if(! test -e "tetris.c.o"); then
        echo "Build failed."; exit
    fi

    echo "*** Preprocessing and assembling the resource_${1:-"EN"} script (resource_${1:-"EN"}.rc)..."
    if(test -e "resource_${1:-"EN"}.rc.o"); then
        rm -f "resource_${1:-"EN"}.rc.o"
    fi
    arm-mingw32ce-windres resource_${1:-"EN"}.rc resource_${1:-"EN"}.rc.o
    if(! test -e "resource_${1:-"EN"}.rc.o"); then
        echo "Build failed."; exit
    fi

    echo "*** Linking tetris.c.o and resource_${1:-"EN"}.rc.o..."
    arm-mingw32ce-gcc tetris.c.o resource_${1:-"EN"}.rc.o -static -s -lcommctrl -o AppMain_${1:-"EN"}.exe
    if(! test -e "AppMain_${1:-"EN"}.exe"); then
        echo "Build failed."; exit
    fi

    rm -rf "tetris.c.o" "resource_${1:-"EN"}.rc.o"

else # Without Resource Script
    echo "*** Building the C source (tetris.c)..."
    arm-mingw32ce-gcc -D LANG_${1:-"EN"} -Wall -O3 -march=armv5tej -mcpu=arm926ej-s -static -s -lcommctrl -o AppMain_${1:-"EN"}.exe tetris.c
    if(! test -e "AppMain_${1:-"EN"}.exe"); then
        echo "Build failed."; exit
    fi
fi

echo "Build successful."