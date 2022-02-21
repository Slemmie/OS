# compile boot sector
# requires assembly compiler 'nasm'
# $ apt install nasm

# compile kernel
cd kernel && gcc -ffreestanding -c kernel.c -o kernel.o
ld -o ../kernel.bin -Ttext 0x1000 kernel.o --oformat binary
cd ..

# compile boot sector
cd boot_sector && nasm -f bin boot.asm -o ../boot.bin
cd ..

# make image
cat boot.bin kernel.bin > os-image

echo "DONE"
