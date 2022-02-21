# OS
Miserably failing at creating an operating system!
# Usage
make cimpler script and runner script executable:

	$ chmod +x compile.sh
	$ chmod +x run.sh

to compile, then run the system (using qemu):

	$ ./compile.sh
	$ ./run.sh

# Dependencies
- nasm (assembler)
- qemu (machine emulator)

#### Installation (probably requires sudo privileges):

	$ apt install nasm
	$ apt install qemu-system-x86
