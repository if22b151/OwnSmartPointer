@echo off
mkdir winBuild
pushd winBuild
    cl ../main.cpp /ZI /EHsc /DEBUG /std:c++20
popd
devenv .\winBuild\main.exe