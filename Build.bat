@echo off
cmake -G "MinGW Makefiles" -B BuildCache
cd BuildCache
mingw32-make
pause