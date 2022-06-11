#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "./timer.cpp"

int main(int argc, char *argv[]) {
    Timer *t = new Timer(15000);
    t -> start();

    return 0;
}
