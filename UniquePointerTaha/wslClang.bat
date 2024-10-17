@echo off
mkdir wslClangBuild
pushd wslClangBuild
wsl clang++ -std=c++20 ../main.cpp -o main
popd
wsl wslClangBuild/main
pause