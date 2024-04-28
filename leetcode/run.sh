#!/bin/bash

if g++ -D_GLIBCXX_DEBUG -Wall -fsanitize=address,undefined -g -DLC_LOCAL -std=c++20 $1 ; then
	./a.out
fi