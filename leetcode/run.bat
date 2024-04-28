@echo off

REM AddressSanitizer and UndefinedSanitizer are not supported on Windows' GCC builds
g++ -D_GLIBCXX_DEBUG -Wall -g -DLC_LOCAL -std=c++20 %1 && .\a.exe