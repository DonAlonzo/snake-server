#!/usr/bin/env bash

git pull

mkdir -p build
cd build
rm -rf *
cmake ..
make

screen -ls | awk -vFS='\t|[.]' '/snake-server/ {system("screen -S "$2" -X quit")}'
screen -dmSL snake-server ../bin/snake-server
