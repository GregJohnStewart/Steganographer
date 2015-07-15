#!/bin/bash
# compiles the stenographer program

cd res/
g++ -c Stenographer.cpp
cd ..
g++ -c main.cpp

g++ -o Stenographer main.o res/Stenographer.o
