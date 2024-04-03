#include <system.h>
#include <serial.h>
#include <ps2.h>
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
    term_initialise();
    init_Timer(1000);
    ascii_title();
    printf("\n\n ~ $");
    sleep(100);
    printf("Has a second passed? YOU DECIDE\n");
    char array[4];
    printf("array: %c",array[4000000000]);
    
    
    
    
    
}
