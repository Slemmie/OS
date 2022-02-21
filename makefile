# build everything :)

# dependencies:
	# gcc
	# ld
	# nasm
	# make
	# qemu-system-x86 (for run target)

# full paths
ROOT_PATH = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BIN_PATH = $(ROOT_PATH)/bin

# silent - makes sure bin/ directory exists
prep = @if [ ! -d "$(BIN_PATH)" ]; then mkdir -p $(BIN_PATH); fi;

# main target - run this for a normal build: $ make
all: os-image
	make clean

# run target - run using qemu
run: all
	qemu-system-x86_64 $(ROOT_PATH)/os-image

# os-image target
os-image: $(BIN_PATH)/boot.bin $(BIN_PATH)/kernel.bin
	cat $^ > os-image

# C source files - kernel stuff + driver stuff
C_SOURCE_FILES = $(wildcard $(ROOT_PATH)/kernel/*.c $(ROOT_PATH)/drivers/*.c)
# C header files - kernel stuff + dirver suff
C_HEDAER_FILES = $(wildcard $(ROOT_PATH)/kernel/*.h $(ROOT_PATH)/drivers/*.h)
# C object files
C_OBJ_FILES = ${C_SOURCE_FILES:.c=.o}

#somehing.c -> (path)/somehing.o

# kernel binary file
$(BIN_PATH)/kernel.bin: $(BIN_PATH)/kernel_entry.o ${C_OBJ_FILES}
	$(prep)
	ld -Ttext 0x1000 --oformat binary $^ -o $@

# C object files
%.o: %.c ${C_HEADER_FILES}
	gcc -ffreestanding -c $< -o $@

# kernel entry object file
$(BIN_PATH)/kernel_entry.o: $(ROOT_PATH)/boot_sector/kernel_entry.asm
	$(prep)
	nasm -f elf64 $^ -o $@

# boot sector binary
$(BIN_PATH)/boot.bin: $(ROOT_PATH)/boot_sector/boot.asm
	$(prep)
	cd $(ROOT_PATH)/boot_sector/ && nasm -f bin boot.asm -o $@

# clean target - remove temporary files
.PHONY: clean
clean:
	rm -rf ./bin
	rm -rf *.bin *.o
	rm -rf kernel/*.o boot_sector/*.bin drivers/*.o
