#include <system.h>
#include <serial.h>
#include <printf.h>
#include <timer.h>



void init_Timer(uint32_t reload_value){
    timerticks = 0;
    uint32_t timerFrequency = TIMER_ACCURACY / reload_value;

    outportb(0x43, 0x36);

    debugf("%x\n",timerFrequency & 0xFF);

    uint8_t l = (uint8_t) (timerFrequency & 0xFF);
    uint8_t h = (uint8_t) (timerFrequency >> 8 & 0xFF);

    outportb(0x40, l);
    outportb(0x40, h);
    debugf("[timer] Current timer frequency: %dMHz\n",timerFrequency);
}

void timer_handler(){
    timerticks++;
}

void sleep(uint32_t timeValue) {
    uint64_t target = timerticks + (timeValue*1000);
    while (target > timerticks){
    } 
}

