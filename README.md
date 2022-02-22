# OS
Miserably failing at creating an operating system!

# Usage
To run the system, simply (using qemu):

	$ make run

To make the os-image without running directly in qemu (can be used in other emulators/installed onto somewhere):

	$ make

Simply compiling does not require qemu as a dependency.

# Dependencies (see Installation...)
- nasm (assembler)
- gcc (C compiler)
- make (build system)
- ld (linker)
- qemu-system-x86 (machine emulator) (is not required for raw building of the os-image)

#### Installation (probably requires sudo privileges):

	$ apt install nasm
	$ apt install gcc
	$ apt install make
	$ apt install binutils (for ld linker tool)
	$ apt install qemu-system-x86

These packages are common, and should also exist in other mainstream package managers (like PacMan, etc.).
