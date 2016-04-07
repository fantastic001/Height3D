#!/bin/sh
g++ -o test -lboost_unit_test_framework functional/*.cpp core/*.cpp gui/*.cpp \
	-lGL -lGLEW -I/usr/include/SDL2 -L/usr/lib -lSDL2 -I.
./test
rm test
