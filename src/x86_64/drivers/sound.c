#include "sound.h"
#include "ports.h"
#include "pic.h"

void play_sound(uint32 freq)
{
   uint32 divisor;
   uint8 sound;

   divisor = 1193180 / freq;
   outb(PORT_PIT_CMD_WRONLY, 0xb6);
   outb(PORT_PIT2_IO, (uint8)(divisor));
   outb(PORT_PIT2_IO, (uint8)(divisor >> 8));
   sound = inb(PORT_PIT2_HP);
   if (sound != (sound | 0x3))
       outb(PORT_PIT2_HP, sound | 0x3);
}

void sound_off(void)
{
    outb(PORT_PIT2_HP, (inb(PORT_PIT2_HP) & 0xFC));
}

void beep(void)
{
    for (int i = 1; i < 50000; i++) {
        play_sound(10);
        io_delay();
        io_delay();
        io_delay();
        if (i >= 10000)
            i = 1;
    }
    sound_off();
}
