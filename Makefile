default: build

build: build-setup linux win

build-setup:
	if [ -d "build" ]; then rm -rf build; fi
	mkdir build

linux:
	aarch64-linux-gnu-g++ src/main.cpp -o build/bpc-linux-aarch64
	alpha-linux-gnu-g++ src/main.cpp -o build/bpc-linux-alpha
	arm-linux-gnueabi-g++ src/main.cpp -o build/bpc-linux-arm-gnueabi
	arm-linux-gnueabihf-g++ src/main.cpp -o build/bpc-linux-arm-gnueabihf
	i686-linux-gnu-g++ src/main.cpp -o build/bpc-linux-i686
	m68k-linux-gnu-g++ src/main.cpp -o build/bpc-linux-m68k
	mips-linux-gnu-g++ src/main.cpp -o build/bpc-linux-mips
	mipsel-linux-gnu-g++ src/main.cpp -o build/bpc-linux-mipsel
	powerpc-linux-gnu-g++ src/main.cpp -o build/bpc-linux-ppc
	powerpc64-linux-gnu-g++ src/main.cpp -o build/bpc-linux-ppc64
	powerpc64le-linux-gnu-g++ src/main.cpp -o build/bpc-linux-ppc64le
	riscv64-linux-gnu-g++ src/main.cpp -o build/bpc-linux-riscv64
	s390x-linux-gnu-g++ src/main.cpp -o build/bpc-linux-s390x
	sh4-linux-gnu-g++ src/main.cpp -o build/bpc-linux-sh4
	sparc64-linux-gnu-g++ src/main.cpp -o build/bpc-linux-sparc64
	x86_64-linux-gnu-g++ src/main.cpp -o build/bpc-linux-x86_64

win:
	x86_64-w64-mingw32-g++ src/main.cpp -o build/bpc-windows-x64.exe
	i686-w64-mingw32-g++ src/main.cpp -o build/bpc-windows-x86.exe

run: build run-linux

run-linux:
	@echo "----------------------------------------------------------"
	./build/bpc-linux
