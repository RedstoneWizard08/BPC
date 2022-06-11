#include "./timer.cpp"
#include "./window.cpp"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
    Timer *t = new Timer(15000);
    t -> start();

    return 0;
}
