#!/bin/sh
g++ *.cpp core/*.cpp \
	gui/*.cpp \
	-o tutorial1 -lGL -lGLEW -I/usr/include/SDL2 -L/usr/lib -lSDL2

