#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "./timer.cpp"

int main() {
    printf("Hello, %s!\n", getenv("USER"));
    return 0;
}
