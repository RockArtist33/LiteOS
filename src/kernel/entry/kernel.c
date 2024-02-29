#include <system.h>
#include <serial.h>
#include <timer.h>
#include <vga.h>
#include <printf.h>

void ascii_title() {
    printf("==========================================\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|    _      _  _           ___   ____    |\n");
    printf("|   | |    (_)| |_   ___  / _ \\ / ___|   | \n");
    printf("|   | |    | || __| / _ \\| | | |\\___ \\   | \n");
    printf("|   | |___ | || |_ |  __/| |_| | ___) |  |\n");
    printf("|   |_____||_| \\__| \\___| \\___/ |____/   |\n");
    printf("|                                        |\n");
    printf("|             Version: 0.0.0             |\n");
    printf("|                                        |\n");
    printf("==========================================   \n\n");
}

void kernel_main(void) {
    int COM1 = 0x3F8;
    int PS2_CONTROLLER = 0x64;
    int PS2 = 0x60;
    term_initialise();
    init_Timer(1000);
    init_serial(COM1);
    ascii_title();
    printf("\n\n ~ $");
    debugf("AN actual shell would start here if I HAD IT\n");
    serial_write(PS2_CONTROLLER, 0xAE);
    int previous_keyboard_command;
    previous_keyboard_command = 0;
    while (true)
    {
        if ((serial_read(PS2) != previous_keyboard_command) && (serial_read(PS2) <= 0xffff0000)) {
            printf("%c", serial_read(PS2));
            previous_keyboard_command = serial_read(PS2);
        }
        else if ((serial_read(PS2) != previous_keyboard_command)) {
            previous_keyboard_command = 0xffffff;
        }
    }
    
    
    
}