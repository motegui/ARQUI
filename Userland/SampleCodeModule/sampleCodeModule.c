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
		}
	else{
		sys_write(buffer, WHITE);
	}
}


int main() {
	sys_write(">", WHITE);
	while(1){
		scanf(buffer, BUFFER_SIZE);
		command(buffer);
		enter();
		sys_write(">", WHITE);
	}

	return 0;
}