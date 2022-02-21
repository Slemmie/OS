# compile boot sector
# requires assembly compiler 'nasm'
# $ apt install nasm

# compile kernel
cd kernel
gcc -ffreestanding -c kernel.c -o ../bin/kernel.o
cd ..
#ld -o ../kernel.bin -Ttext 0x1000 kernel.o --oformat binary

#compiler kernel entry
cd boot_sector
nasm kernel_entry.asm -f elf64 -o ../bin/kernel_entry.o
cd ..

# compile boot sector
cd boot_sector
nasm -f bin boot.asm -o ../bin/boot.bin
cd ..

# link
ld -o ./bin/kernel.bin -Ttext 0x1000 ./bin/kernel_entry.o ./bin/kernel.o --oformat binary

# make image
cat ./bin/boot.bin ./bin/kernel.bin > ./bin/os-image

echo "DONE"
