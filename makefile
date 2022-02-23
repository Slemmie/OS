# building/running the os image
# [to build (not run)]: $ make
# [to build, then run]: $ make run

# full path to here...
ROOT_PATH = $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

# os-image full name
OS_IMAGE = $(ROOT_PATH)/os-image

# main target
all: $(OS_IMAGE)
	make clean

# compile then emulate inside qemu
run: all
	qemu-system-x86_64 $(OS_IMAGE)

# os-image target
$(OS_IMAGE): $(ROOT_PATH)/boot_loader/boot_loader.bin $(ROOT_PATH)/kernel/kernel.bin
	cat $^ > os-image

###########################
### BOOT LOADER SECTION ###
###########################

# list of boot loader asm files
BOOT_LOADER_ASM_FILES =                         \
$(wildcard $(ROOT_PATH)/boot_loader/*.asm)      \
$(wildcard $(ROOT_PATH)/boot_loader/util/*.asm) \

# boot loader binary
$(ROOT_PATH)/boot_loader/boot_loader.bin: $(BOOT_LOADER_ASM_FILES)
	cd $(ROOT_PATH)/boot_loader/ && nasm -f bin boot_loader.asm -o $@

######################
### KERNEL SECTION ###
######################

# C SOURCE FILES
C_SOURCE_FILES = \
$(wildcard $(ROOT_PATH)/kernel/*.c)
# C HEADER FILES
C_HEADER_FILES = \
$(wildcard $(ROOT_PATH)/kernel/*.h)
# C OBJECT FILES
C_OBJECT_FILES = ${C_SOURCE_FILES:.c=.o}

# C files compilation
%.o: %.c ${C_HEADER_FILES}
	x86_64-elf-gcc -ffreestanding -mno-red-zone -m64 -c $< -o $@

# linking
$(ROOT_PATH)/kernel/kernel.bin: $(ROOT_PATH)/boot_loader/extended_program.o ${C_OBJECT_FILES}
	custom-ld -m elf_x86_64 -Ttext 0x7e00 --oformat binary -o $@ $^

# boot loader: extended program object file
$(ROOT_PATH)/boot_loader/extended_program.o: $(BOOT_LOADER_ASM_FILES)
	cd $(ROOT_PATH)/boot_loader/ && nasm -f elf64 extended_program.asm -o $@

##########################
### DEPENDENCY SECTION ###
##########################

# make dependencies
# needs to be run just once
# targets debian/mint/alike.
# run with sudo
.PHONY: deps
make deps:
	apt install -y nasm
	apt install -y gcc
	apt install -y binutils
	apt install -y build-essential
	apt install -y bison
	apt install -y flex
	apt install -y libgmp3-dev
	apt install -y libmpc-dev
	apt install -y libmpfr-dev
	apt install -y texinfo
	apt install -y curl
	apt install -y gcc-multilib
	
	export PREFIX="/usr/local/x86_64elfgcc"
	export TARGET=x86_64-elf
	export PATH="$$PREFIX/bin:$$PATH"
	
	if [ ! -d "/tmp/src/" ]; then mkdir -p /tmp/src/; fi && \
	cd /tmp/src/ && \
	curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.35.1.tar.gz && \
	mkdir -p binutils-build && cd binutils-build && \
	../binutils-2.35.1/configure --target=$$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$$PREFIX 2>&1 | tee configure.log && \
	make all install 2>&1 | tee make.log && \
	cd /tmp/src/ && \
	curl -O https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz && \
	tar xf gcc-10.2.0.tar.gz && \
	if [ -d "gcc-build/" ]; then rm -rf gcc-build/; fi && \
	mkdir -p gcc-build/ && cd gcc-build/  && \
	../gcc-10.2.0/configure --target=$$TARGET --prefix="$$PREFIX" --disable-nls --disable-libssp --enable-languages=c++ --without-headers && \
	make all-gcc && \
	make all-target-libgcc && \
	make install-gcc && \
	make install-target-libgcc

#######################
### UTILITY SECTION ###
#######################
# cleans up temporary files
.PHONY: clean
clean:
	rm -rf $(ROOT_PATH)/boot_loader/*.o
	rm -rf $(ROOT_PATH)/boot_loader/*.bin
	rm -rf $(ROOT_PATH)/boot_loader/util/*.o
	rm -rf $(ROOT_PATH)/boot_loader/util/*.bin
	rm -rf $(ROOT_PATH)/kernel/*.o
	rm -rf $(ROOT_PATH)/kernel/*.bin
	rm -rf $(ROOT_PATH)/*.o
	rm -rf $(ROOT_PATH)/*.bin
	
