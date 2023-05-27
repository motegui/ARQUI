/* sampleCodeModule.c */
#include <stdint.h>
#include <time_driver.h>
#include <user_syscalls.h>
#include <functions.h>

#define BUFFER_SIZE 50


 char buffer[BUFFER_SIZE];

void command(char * entry){
	if(strcmp(buffer, "TIME")==0){
			getTime(WHITE);
			enter();
		}
	else if(strcmp(buffer, "CLEAR")==0){
		sys_clear_screen();
	}
	else{
		sys_write(buffer, WHITE);
		enter();
	}
}


int main() {
	sys_write(">", WHITE);
	while(1){
		scanf(buffer, BUFFER_SIZE);
		command(buffer);
		sys_write(">", WHITE);
	}

	return 0;
}