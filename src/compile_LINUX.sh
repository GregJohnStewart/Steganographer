#!/bin/bash
# compiles the stenographer program

cd res/
g++ -c Stenographer.cpp
cd ..
g++ -c main.cpp


g++ -g -o ../bin/Stenographer_x64_ubuntu main.o res/Stenographer.o 
