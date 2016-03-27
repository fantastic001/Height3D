#!/bin/sh
g++ *.cpp core/*.cpp \
	-o tutorial1 -lGL -lGLEW -I/usr/include/SDL2 -L/usr/lib -lSDL2

