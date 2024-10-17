@echo off
mkdir wslG++Build
pushd wslG++Build
wsl g++ -std=c++17 ../main.cpp -o main
popd
wsl wslG++Build/main
pause