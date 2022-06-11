#!/bin/bash

sudo apt-get update
sudo apt-get -y install \
    g++-aarch64-linux-gnu g++-alpha-linux-gnu g++-arm-linux-gnueabi g++-arm-linux-gnueabihf \
    g++-i686-linux-gnu g++-m68k-linux-gnu g++-mips-linux-gnu g++-mipsel-linux-gnu \
    g++-powerpc-linux-gnu g++-powerpc64-linux-gnu g++-powerpc64le-linux-gnu g++-riscv64-linux-gnu \
    g++-s390x-linux-gnu g++-sh4-linux-gnu g++-sparc64-linux-gnu g++-x86-64-linux-gnu \
    g++-mingw-w64-i686 g++-mingw-w64-x86-64 g++-mingw-w64 g++ make
