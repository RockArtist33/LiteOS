#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <system.h>

#define COM_PORT1 0x3F8 //COM1

int init_serial(int port_device) {
   outportb(port_device + 1, 0x00);    // Disable all interrupts
   outportb(port_device + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outportb(port_device + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outportb(port_device + 1, 0x00);    //                  (hi byte)
   outportb(port_device + 3, 0x03);    // 8 bits, no parity, one stop bit
   outportb(port_device + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outportb(port_device + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outportb(port_device + 4, 0x1E);    // Set in loopback mode, test the serial chip
   outportb(port_device + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
    if (inportb(port_device+0) != 0xAE) {
        printf("inportb value: %X\n",inportb(port_device+0));
        return 1;
    }

    outportb(port_device + 4, 0X0F);
    return 0;

}

int serial_received(int device_port) {
    return inportb(device_port + 5) & 1;;
}

char serial_read(int device_port) {
    while (serial_received(device_port) == 0);
    return inportb(device_port);
}

int is_transmission_empty(int port_device) {
    return inportb(port_device + 5) & 0x20;
}

void serial_write(int device_port, char a) {
    while (is_transmission_empty(device_port) == 0);
    outportb(device_port, a);
}

void debug(char c, void *arg) {
    if ((c == '\n')) {
        serial_write(COM_PORT1, '\r');
    }
    serial_write(COM_PORT1, c);
}

int debugf(const char * format, ... ) {
    va_list va;
    va_start(va, format);
    int ret = vfctprintf(debug, 0, format, va);
    va_end(va);
    return ret;
}