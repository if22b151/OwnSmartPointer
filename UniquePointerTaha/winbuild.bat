@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 > nul

set "dirPath=C:\Taha\Studium\Semester5\EPC\UniquePointer\winBuild"

if not exist "%dirPath%" (
    mkdir winBuild
)

pushd winBuild
    cl /nologo ../main.cpp /ZI /EHsc /DEBUG /std:c++20 
popd
