#include <system.h>
#include <serial.h>
#include <printf.h>
#include <timer.h>



void init_Timer(uint32_t reload_value){
    timerticks = 0;
    seconds = 0;
    timerFrequency = TIMER_ACCURACY / reload_value;

    outportb(0x43, 0x36);

    uint8_t l = (uint8_t) (timerFrequency & 0xFF);
    uint8_t h = (uint8_t) (timerFrequency >> 8 & 0xFF);

    outportb(0x40, l);
    outportb(0x40, h);
    debugf("Current timer frequency: %dMHz\n",timerFrequency);
}

void timer_handler(){
    timerticks++;
}
