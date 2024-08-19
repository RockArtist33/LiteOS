#include <system.h>
#include <serial.h>
#include <keyboard.h>
#include <printf.h>

#define PS2_CONTROLLER_COM 0x64
#define PS2_DATA_PORT 0x60

char KeyboardCharacters[128] = {
    0x00, 0x01, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', 0x0E, 0x0F, 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0x1C, 0x1D,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k','l', ';', '\'',
    '`', 0x2A, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',',
    '.', '/', 0x36, '*', 0x38, ' ', 0x3A, 0x3B, 0x3C, 0x3D,
    0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, '7',
    '8', '9', '-', '4', '5', '6', '+', '1', '2', '3',
    '0', '.', 0x57, 0x58
};

void DetectIncomingChar() {
    int KeyboardInput = serial_read(PS2_DATA_PORT);
    if (KeyboardInput & 0x80) return;
    printf("%c", KeyboardCharacters[KeyboardInput]);
    return;
}
/*
int keyboard_interrupt() {
  serial_write(PS2_CONTROLLER_COM, 0xAE);
  int previous_keyboard_command;
  int input = serial_read(PS2_PORT_1);
  if ((input != previous_keyboard_command) && (input <= 0xffff0000)) {
      char RESULT_KEY;
  RESULT_KEY = KEYCODE_CHAR[input];
  printf("%c", RESULT_KEY);
  debugf("KEY: %c, INPUT:%X\n", RESULT_KEY, serial_read(PS2_PORT_1));
  previous_keyboard_command = serial_read(PS2_PORT_1);
  }
  else if ((serial_read(PS2_PORT_1) != previous_keyboard_command)) {
    previous_keyboard_command = 0xffffff;
  }
}
*/