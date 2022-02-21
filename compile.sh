# compile boot sector
# requires assembly compiler 'nasm'
# $ apt install nasm

cd boot_sector && nasm -f bin boot.asm -o ../boot.bin

echo "DONE"
