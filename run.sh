if g++ -D_GLIBCXX_DEBUG -Wall -DLC_LOCAL -std=c++17 main.cpp ; then
    cd . > output.txt
    ./a.out
    printf "\n"
    cat output.txt
    printf "\n"
fi