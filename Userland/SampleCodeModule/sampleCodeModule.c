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
	sys_write("HELP", GREEN);
	sys_write(": to get the information on the available commands", WHITE);
	enter();
	sys_write("TIME", GREEN);
	sys_write(": to get the current time", WHITE);
	enter();
	sys_write("CLEAR", GREEN);
	sys_write(": to clear the terminal", WHITE);
	enter();
	sys_write("PONG", GREEN);
	sys_write(": to play game", WHITE);
	enter();
	sys_write("REGISTERS", GREEN);
	sys_write(": to print register status", WHITE);
	enter();
}


void command(char * entry){
	deleteInitialFinalSpace(buffer);
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
	else if(strcmp(buffer, "PONG")==0){
		pong();
	}
	else if(strcmp(buffer, "REGISTERS")==0){
		getRegInfo();
		enter();
	}
	else if(strcmp(buffer, "REGSTESTER")==0){
		print("r10 tiene que valer A, r9: 5, rcx: 8");
		print("apretar control ahora");
		testRegs();
		enter();
	}
	else{
		sys_write(buffer, WHITE);
		enter();
	}
}


int main() {
	sys_write("Welcome!", PURPLE);
	enter();
	help();
	while(1){
		sys_write(">", BLUE);
		scanf(buffer, BUFFER_SIZE);
		command(buffer);
	}

	return 0;
}