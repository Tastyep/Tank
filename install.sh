#!/bin/sh

mkdir -p build && cd build
cmake ..
echo ""
read -p "Number of thread used for compilation (default 4): " nbThreads
nbThreads=${nbThreads:-4}
make -j$nbThreads
