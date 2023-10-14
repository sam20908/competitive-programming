@echo off
g++ -D_GLIBCXX_DEBUG -Wall -fsanitize=undefined -DLC_LOCAL -std=c++20 main.cpp && goto exec
exit /B 1
:exec
.\a.out
echo.
type output.txt
echo.