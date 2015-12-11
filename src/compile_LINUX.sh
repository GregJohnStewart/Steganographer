#!/bin/bash
# compiles the stenographer program

cd res/
g++ -c Steganographer.cpp -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
cd ..
g++ -c main.cpp


g++ -g -o ../bin/Stenographer_x64_ubuntu main.o res/Steganographer.o -O2 -L/usr/X11R6/lib -lm -lpthread -lX11
