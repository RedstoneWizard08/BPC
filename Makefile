CPP_OPTS := -v

default: build

build: build-setup linux win finish

build-setup:
	@if [ -d "build" ]; then rm -rf build; fi
	@mkdir build

linux:
	@echo "Building linux-arm64..." | tee build.log
	@aarch64-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-aarch64 >> build.log 2>&1

	@echo "Building linux-alpha..." | tee -a build.log
	@alpha-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-alpha >> build.log 2>&1
	
	@echo "Building linux-arm..." | tee -a build.log
	@arm-linux-gnueabi-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-arm >> build.log 2>&1
	
	@echo "Building linux-armhf..." | tee -a build.log
	@arm-linux-gnueabihf-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-armhf >> build.log 2>&1

	@echo "Building linux-i686..." | tee -a build.log
	@i686-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-i686 >> build.log 2>&1
	
	@echo "Building linux-m68k..." | tee -a build.log
	@m68k-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-m68k >> build.log 2>&1
	
	@echo "Building linux-mips..." | tee -a build.log
	@mips-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-mips >> build.log 2>&1
	
	@echo "Building linux-mipsel..." | tee -a build.log
	@mipsel-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-mipsel >> build.log 2>&1
	
	@echo "Building linux-ppc..." | tee -a build.log
	@powerpc-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-ppc >> build.log 2>&1
	
	@echo "Building linux-ppc64..." | tee -a build.log
	@powerpc64-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-ppc64 >> build.log 2>&1
	
	@echo "Building linux-ppc64le..." | tee -a build.log
	@powerpc64le-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-ppc64le >> build.log 2>&1
	
	@echo "Building linux-riscv64..." | tee -a build.log
	@riscv64-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-riscv64 >> build.log 2>&1
	
	@echo "Building linux-s390x..." | tee -a build.log
	@s390x-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-s390x >> build.log 2>&1
	
	@echo "Building linux-sh4..." | tee -a build.log
	@sh4-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-sh4 >> build.log 2>&1
	
	@echo "Building linux-sparc64..." | tee -a build.log
	@sparc64-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-sparc64 >> build.log 2>&1
	
	@echo "Building linux-x86_64..." | tee -a build.log
	@x86_64-linux-gnu-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-linux-x86_64 >> build.log 2>&1

win:
	@echo "Building windows-x86_64..." | tee -a build.log
	@x86_64-w64-mingw32-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-windows-x64.exe >> build.log 2>&1

	@echo "Building windows-i686..." | tee -a build.log
	@i686-w64-mingw32-g++ $(CPP_OPTS) src/main.cpp -o build/bpc-windows-x86.exe >> build.log 2>&1

finish:
	@echo "Packing executables..." | tee -a build.log
	@upx --best build/bpc-linux-aarch64 build/bpc-linux-mips build/bpc-linux-mipsel \
		build/bpc-linux-ppc build/bpc-linux-ppc64 build/bpc-linux-ppc64le \
		build/bpc-windows-x64.exe build/bpc-windows-x86.exe >> build.log 2>&1

	@echo "Testing packed executables..." | tee -a build.log
	@upx -t build/bpc-linux-aarch64 build/bpc-linux-mips build/bpc-linux-mipsel \
		build/bpc-linux-ppc build/bpc-linux-ppc64 build/bpc-linux-ppc64le \
		build/bpc-windows-x64.exe build/bpc-windows-x86.exe >> build.log 2>&1
	
	@echo "Changing permissions of the files..." | tee -a build.log
	@chmod -R a+rx build >> build.log 2>&1

	@echo "Done!" | tee -a build.log

run: build run-linux

run-linux:
	@echo "----------------------------------------------------------"
	./build/bpc-linux-x86_64

dev-build:
	g++ src/main.cpp -o bpc
