#!/bin/bash

if g++ -D_GLIBCXX_DEBUG -Wall -fsanitize=address,undefined -g -DLC_LOCAL -std=c++20 main.cpp ; then
    ./a.out < input.txt > output.txt
    cat output.txt
fi