@echo off
path C:\MinGW64\bin\;C:\MinGW64\libexec\gcc\mingw32\4.8.1\;%path%
g++ %1.cpp -o %1.exe
echo on
