all:
	rm -f *.o *.tmp kernel.bin
	nasm -f win32 boot.asm -o boot.o
	g++ -m32 -c kernel.cpp -o kernel.o -ffreestanding -O2 -fno-exceptions -fno-rtti
	ld -m i386pe -T linker.ld -o kernel.tmp boot.o kernel.o
	objcopy -S -O elf32-i386 kernel.tmp kernel.bin

run:
	qemu-system-i386 -kernel kernel.bin