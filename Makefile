default: build

build: build-setup linux win

build-setup:
	if [ -d "build" ]; then rm -rf build; fi
	mkdir build

linux:
	g++ src/main.cpp -o build/bpc-linux

win: win64 win32

win64:
	x86_64-w64-mingw32-g++ src/main.cpp -o build/bpc-win64.exe

win32:
	i686-w64-mingw32-g++ src/main.cpp -o build/bpc-win32.exe

run: build run-linux

run-linux:
	@echo "----------------------------------------------------------"
	./build/bpc-linux
