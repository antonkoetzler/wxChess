#!/bin/bash
cmake -G "Unix Makefiles" -S ./ -B ./build
cd build
cp -r ../img ./img
make
$SHELL
