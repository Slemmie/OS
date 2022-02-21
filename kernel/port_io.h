// communication with I/O addresses

typedef unsigned short IO_port;

unsigned char port_byte_in(IO_port port);
unsigned short port_word_in(IO_port port);
void port_byte_out(IO_port port, unsigned char data);
void port_word_out(IO_port port, unsigned short data);
