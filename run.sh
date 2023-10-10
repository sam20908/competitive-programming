if g++ -D_GLIBCXX_DEBUG -Wall -DLC_LOCAL -std=c++20 main.cpp ; then
    ./a.out
    printf "\n"
    cat output.txt
    printf "\n"
fi