#ifndef SERIAL_H
#define SERIAL_h

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static int init_serial(int device_port);
int serial_received(int device_port);
char serial_read(int device_port);
int is_transmission_empty(int device_port);
void serial_write(int device_port, char a);
int debugf(const char * format, ... );

#endif

