/* sampleCodeModule.c */
#include <stdint.h>
#include <time_driver.h>
#include <user_syscalls.h>
#include <functions.h>

#define BUFFER_SIZE 50


char buffer[BUFFER_SIZE];

void help(){
	sys_write("The available commands are:", WHITE);
	enter();
	sys_write("HELP: to get the information on the available commands", WHITE);
	enter();
	sys_write("TIME: to get the current time", WHITE);
	enter();
	sys_write("CLEAR: to clear the terminal", WHITE);
	enter();
}


void command(char * entry){
	if(strcmp(buffer, "TIME")==0){
			getTime(WHITE);
			enter();
		}
	else if(strcmp(buffer, "CLEAR")==0){
		sys_clear_screen();
	}
	else if(strcmp(buffer, "HELP")==0){
		help();
	}
	else{
		sys_write(buffer, WHITE);
		enter();
	}
}


int main() {
	sys_write("Welcome!", WHITE);
	enter();
	help();
	sys_write(">", WHITE);
	while(1){
		scanf(buffer, BUFFER_SIZE);
		command(buffer);
		sys_write(">", WHITE);
	}

	return 0;
}