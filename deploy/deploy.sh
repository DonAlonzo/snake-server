#!/usr/bin/env bash

git -C .. pull

mkdir -p ../build
cd ../build
rm -rf *
cmake ..
make
