# building/running the os image
# [to build (not run)]: $ make
# [to build, then run]: $ make run

# os-image full name
OS_IMAGE = ./os-image

# main target
all: $(OS_IMAGE)
	make clean

# compile then emulate inside qemu
run: all
	qemu-system-x86_64 $(OS_IMAGE)

# os-image target
$(OS_IMAGE): ./boot_loader/boot_loader.bin ./kernel/kernel.bin
	cat $^ > os-image

###########################
### BOOT LOADER SECTION ###
###########################

# list of boot loader asm files
BOOT_LOADER_ASM_FILES =              \
$(wildcard ./boot_loader/*.asm)      \
$(wildcard ./boot_loader/util/*.asm) \

# boot loader binary
./boot_loader/boot_loader.bin: $(BOOT_LOADER_ASM_FILES)
	cd ./boot_loader/ && nasm -f bin boot_loader.asm -o ../$@
#	cd ./boot_loader/ && nasm -f bin boot_loader.asm -o boot_loader.bin

######################
### KERNEL SECTION ###
######################

# C SOURCE FILES
C_SOURCE_FILES =                          \
$(wildcard ./kernel/*.c)                  \
$(wildcard ./kernel/util/*.c)             \
$(wildcard ./kernel/vidmem/*.c)           \
$(wildcard ./kernel/drivers/*.c)          \
$(wildcard ./kernel/drivers/keyboard/*.c)
# C HEADER FILES
C_HEADER_FILES =                          \
$(wildcard ./kernel/*.h)                  \
$(wildcard ./kernel/util/*.h)             \
$(wildcard ./kernel/vidmem/*.h)           \
$(wildcard ./kernel/drivers/*.h)          \
$(wildcard ./kernel/drivers/keyboard/*.h)
# C OBJECT FILES
C_OBJECT_FILES = ${C_SOURCE_FILES:.c=.o}

# kernel linker script
KERNEL_LINKER = link.ld

# C files compilation
%.o: %.c ${C_HEADER_FILES}
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c $< -o $@
#	/usr/local/x86_64elfgcc/bin/x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c $< -o $@

# linking
kernel/kernel.bin: boot_loader/extended_program.o ${C_OBJECT_FILES}
	ld -T"$(KERNEL_LINKER)" -nostdlib
#	/usr/local/x86_64elfgcc/bin/x86_64-elf-ld -T"$(KERNEL_LINKER)"

# boot loader: extended program object file
boot_loader/extended_program.o: $(BOOT_LOADER_ASM_FILES)
	cd ./boot_loader/ && nasm -f elf64 extended_program.asm -o ../$@

##########################
### DEPENDENCY SECTION ###
##########################

###############
## IMPORTANT ############################
# this step is not needed at the moment #
#########################################

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
	
	if [ ! -d "/tmp/src/" ]; then mkdir -p /tmp/src/; fi && \
	cd /tmp/src/ && \
	curl -O https://ftp.gnu.org/gnu/binutils/binutils-2.38.tar.xz && \
	tar xf binutils-2.38.tar.xz && \
	mkdir -p binutils-build && cd binutils-build && \
	../binutils-2.38/configure --target=$$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$$PREFIX 2>&1 | tee configure.log && \
	make all install 2>&1 | tee make.log && \
	cd /tmp/src/ && \
	curl -O https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz && \
	tar xf gcc-10.2.0.tar.gz && \
	if [ -d "gcc-build/" ]; then rm -rf gcc-build/; fi && \
	mkdir -p gcc-build/ && cd gcc-build/ && \
	../gcc-10.2.0/configure --target=$$TARGET --prefix="$$PREFIX" --disable-nls --disable-libssp --enable-languages=all --without-headers && \
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
	find . -name *.o -delete
	find . -name *.bin -delete
