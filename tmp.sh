cd boot_loader && nasm boot_loader.asm -f bin -o ../boot_loader.bin

cd ..

cd boot_loader && nasm extended_program.asm -f elf64 -o ../extended_program.o

cd ..

/usr/local/x86_64elfgcc/bin/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c kernel/kernel.c -o kernel.o

/usr/local/x86_64elfgcc/bin/x86_64-elf-ld -T"link.ld"

cat boot_loader.bin kernel.bin > img
