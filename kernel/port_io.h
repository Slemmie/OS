// communication with I/O bus addresses

#include "util/types.h"

typedef uint_16 IO_port;

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xa0
#define PIC2_DATA    0xa1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

uint_8 port_byte_in(IO_port port);
void port_byte_out(IO_port port, uint_8 data);

void remap_pic();
