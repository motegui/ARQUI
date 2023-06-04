// https://wiki.osdev.org/PC_Speaker

//Play sound using built in speaker
#include <stdint.h>
#include <time.h>
#include <lib.h>
#include <sound.h>

/* Used for sound */
void outb(int memoryMap, int output);
int inb(int memoryMap);

void sleepms(int mseconds);

 //Play sound using built in speaker
void play_sound(int nFrequence) {
 	uint32_t Div;
 	uint8_t tmp;

        //Set the PIT to the desired frequency
 	Div = 1193180 / nFrequence;
 	outb(0x43, 0xb6);
 	outb(0x42, (uint8_t) (Div) );
 	outb(0x42, (uint8_t) (Div >> 8));

        //And play the sound using the PC speaker
 	tmp = inb(0x61);
  	if (tmp != (tmp | 3)) {
 		outb(0x61, tmp | 3);
 	}
 }

 //make it stop
void nosound() {
	uint8_t tmp = inb(0x61) & 0xFC;

	outb(0x61, tmp);
}

 //Make a beep
 void beep(int frec, int time) {
	play_sound(frec);
	sleepms(time);
	nosound();
 }
