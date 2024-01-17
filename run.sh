if g++ -D_GLIBCXX_DEBUG -Wall -fsanitize=undefined -g -DLC_LOCAL -std=c++20 main.cpp ; then
    ./a.out < input.txt > output.txt
    cat output.txt
fi