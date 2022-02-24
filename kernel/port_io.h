// communication with I/O bus addresses

#include "util/types.h"

typedef uint_16 IO_port;

uint_8 port_byte_in(IO_port port);
void port_byte_out(IO_port port, uint_8 data);
