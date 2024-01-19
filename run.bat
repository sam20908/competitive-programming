@echo off
g++ -D_GLIBCXX_DEBUG -Wall -g -DLC_LOCAL -std=c++20 main.cpp && goto exec
exit /B 1
:exec
.\a.exe < input.txt > output.txt
type output.txt