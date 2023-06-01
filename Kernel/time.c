#include <time.h>
#include <lib.h>

static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

// void hold(int delta){ // This function gives us the possibility to wait delta ticks.
// 	int currentTicks = ticks;
// 	while(ticks - currentTicks < delta){
// 		_hlt();
// 	}
// }
void sleepms(int mseconds) {
	int startTime = ticks_elapsed();
	while (mseconds > ticks_elapsed()*18 - startTime*18)
	_hlt();
};
