#include <system.h>
#include <serial.h>
#include <ps2.h>
#include <printf.h>

#define PS2_CONTROLLER_COM 0x64
#define PS2_PORT_1 0x60

enum KEYCODES {
  KEYCODE_1 = 0x02,
  KEYCODE_2 = 0x03,
  KEYCODE_3 = 0x04,
  KEYCODE_4 = 0x05,
  KEYCODE_5 = 0x06,
  KEYCODE_6 = 0x07,
  KEYCODE_7 = 0x08,
  KEYCODE_8 = 0x09,
  KEYCODE_9 = 0x0A,
  KEYCODE_0 = 0x0B,
  KEYCODE_BACKSPACE = 0x0E,
  KEYCODE_Q = 0x10,
  KEYCODE_W = 0x11,
  KEYCODE_E = 0x12,
  KEYCODE_R = 0x13,
  KEYCODE_T = 0x14,
  KEYCODE_Y = 0x15,
  KEYCODE_U = 0x16,
  KEYCODE_I = 0x17,
  KEYCODE_O = 0x18,
  KEYCODE_P = 0x19,
  KEYCODE_ENTER = 0x1C,
  KEYCODE_A = 0x1E,
  KEYCODE_S = 0x1F,
  KEYCODE_D = 0x20,
  KEYCODE_F = 0x21,
  KEYCODE_G = 0x22,
  KEYCODE_H = 0x23,
  KEYCODE_J = 0x24,
  KEYCODE_K = 0x25,
  KEYCODE_L = 0x26,
  KEYCODE_SEMI_COLON = 0x27,
  KEYCODE_LEFT_SHIFT = 0x2A,
  KEYCODE_HASHTAG = 0x2B,
  KEYCODE_Z = 0x2C,
  KEYCODE_X = 0x2D,
  KEYCODE_C = 0x2E,
  KEYCODE_V = 0x2F,
  KEYCODE_B = 0x30,
  KEYCODE_N = 0x31,
  KEYCODE_M = 0x32,
  KEYCODE_COMMA = 0x33,
  KEYCODE_PERIOD = 0x34,
  KEYCODE_SPACE = 0x39,
};




int keyboard_analysis() {
  serial_write(PS2_CONTROLLER_COM, 0xAE);
  int previous_keyboard_command;
  bool SHIFT_KEY_ACYIVE;
  SHIFT_KEY_ACYIVE = false;
  previous_keyboard_command = 0;
  while (true)
  {
    if ((serial_read(PS2_PORT_1) != previous_keyboard_command) && (serial_read(PS2_PORT_1) <= 0xffff0000)) {
      char RESULT_KEY;
     if (serial_read(PS2_PORT_1) == KEYCODE_A) {RESULT_KEY = 'A';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_B) {RESULT_KEY = 'B';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_C) {RESULT_KEY = 'C';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_D) {RESULT_KEY = 'D';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_E) {RESULT_KEY = 'E';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_F) {RESULT_KEY = 'F';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_G) {RESULT_KEY = 'G';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_H) {RESULT_KEY = 'H';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_I) {RESULT_KEY = 'I';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_J) {RESULT_KEY = 'J';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_K) {RESULT_KEY = 'K';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_L) {RESULT_KEY = 'L';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_M) {RESULT_KEY = 'M';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_N) {RESULT_KEY = 'N';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_O) {RESULT_KEY = 'O';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_P) {RESULT_KEY = 'P';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_Q) {RESULT_KEY = 'Q';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_R) {RESULT_KEY = 'R';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_S) {RESULT_KEY = 'S';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_T) {RESULT_KEY = 'T';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_U) {RESULT_KEY = 'U';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_V) {RESULT_KEY = 'V';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_W) {RESULT_KEY = 'W';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_X) {RESULT_KEY = 'X';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_Y) {RESULT_KEY = 'Y';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_Z) {RESULT_KEY = 'Z';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_SPACE) {RESULT_KEY = ' ';}
     else if (serial_read(PS2_PORT_1) == KEYCODE_ENTER) {RESULT_KEY = '\n';}  
     else if (serial_read(PS2_PORT_1) == KEYCODE_BACKSPACE) {RESULT_KEY = '^';}
     else if (serial_read(PS2_PORT_1) == KEYCODE_1) {RESULT_KEY = '1';}
     else if (serial_read(PS2_PORT_1) == KEYCODE_2) {RESULT_KEY = '2';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_3) {RESULT_KEY = '3';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_4) {RESULT_KEY = '4';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_5) {RESULT_KEY = '5';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_6) {RESULT_KEY = '6';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_7) {RESULT_KEY = '7';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_8) {RESULT_KEY = '8';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_9) {RESULT_KEY = '9';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_0) {RESULT_KEY = '0';}
     else if (serial_read(PS2_PORT_1) == KEYCODE_COMMA) {RESULT_KEY = ',';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_PERIOD) {RESULT_KEY = '.';} 
     else if (serial_read(PS2_PORT_1) == KEYCODE_HASHTAG) {RESULT_KEY = '#';}
     else if (serial_read(PS2_PORT_1) == KEYCODE_SEMI_COLON) {RESULT_KEY = ';';}
     else if (serial_read(PS2_PORT_1) == KEYCODE_LEFT_SHIFT) {SHIFT_KEY_ACYIVE = true;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_SEMI_COLON) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = ':';}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_1) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '!'; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_2) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '"'; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_3) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '"'; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_4) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '$'; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_5) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '%'; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_6) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '^'; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_7) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '&'; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_8) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '*'; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_9) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = '('; SHIFT_KEY_ACYIVE = false;}
     else if ((serial_read(PS2_PORT_1) == KEYCODE_0) && (SHIFT_KEY_ACYIVE == true)) {RESULT_KEY = ')'; SHIFT_KEY_ACYIVE = false;}
     printf("%c", RESULT_KEY);
     debugf("KEY: %c, INPUT:%X", RESULT_KEY, serial_read(PS2_PORT_1));

     previous_keyboard_command = serial_read(PS2_PORT_1);
    }
    else if ((serial_read(PS2_PORT_1) != previous_keyboard_command)) {
      previous_keyboard_command = 0xffffff;
    }
  }
}

