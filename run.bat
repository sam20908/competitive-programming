@echo off
g++ -D_GLIBCXX_DEBUG -Wall -DLC_LOCAL -std=c++17 main.cpp && goto exec
echo Compilation unsuccessful
exit /B 1
:exec
.\a.out
echo.
type output.txt
echo.