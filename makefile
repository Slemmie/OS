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
$(OS_IMAGE): $(ROOT_PATH)/boot_loader/boot_loader.bin $(ROOT_PATH)/boot_loader/extended_program.bin
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

# boot loader: extended program binary
$(ROOT_PATH)/boot_loader/extended_program.bin: $(BOOT_LOADER_ASM_FILES)
	cd $(ROOT_PATH)/boot_loader/ && nasm -f bin extended_program.asm -o $@

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
