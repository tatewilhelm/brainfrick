#!/bin/bash

echo "Cloning"
git clone https://github.com/tatewilhelm/brainfrick
cd brainfrick

# Build
cmake CMakeLists.txt
make

# Install
sudo make install

# Clean up
cd ../
rm -rf brainfrick

clear
echo "Installed"