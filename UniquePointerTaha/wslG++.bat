@echo off
mkdir wslG++Build
pushd wslG++Build
wsl g++ -std=c++20 ../main.cpp -o main
popd
wsl wslG++Build/main
pause