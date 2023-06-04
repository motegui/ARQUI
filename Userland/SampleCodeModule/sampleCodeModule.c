/* sampleCodeModule.c */
#include <stdint.h>
#include <time.h>
#include <user_syscalls.h>
#include <functions.h>
#include <exceptionTester.h>
#include <pong.h>
#include <getInfoRegs.h>

#define BUFFER_SIZE 100


char buffer[BUFFER_SIZE];

void help(){

	print("The available commands are:");
	enter();
	sys_write("HELP", GREEN);
	print(": to get the information on the available commands");
	enter();
	sys_write("TIME", GREEN);
	print(": to get the current time");
	enter();
	sys_write("CLEAR", GREEN);
	print(": to clear the terminal");
	enter();
	sys_write("PONG", GREEN);
	print(": to play game");
	enter();
	sys_write("REGISTERS TEST", GREEN);
	print(": to check the correct loading of registers ");
	enter();
	sys_write("REGISTERS", GREEN);
	print(": to print register status");
	enter();
	sys_write("DIVIDE BY ZERO", GREEN);
	print(": to trigger divide by zero exception");
	enter();
	sys_write("INVALID OPERATION", GREEN);
	print(": to trigger invalid operation exception ");
	enter();
}


void command(char * entry){
	deleteExtraSpaces(buffer);
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
	}
	else if(strcmp(buffer, "REGISTERS TEST")==0){
		regsTester();
	}
	else if(strcmp(buffer, "DIVIDE BY ZERO")==0){
		divisionTester();
	}
	else if(strcmp(buffer, "INVALID OPERATION")==0){
		invalidOpTester();
	
	}
	else{
		print("Invalid command");
		enter();
		help();
	}
}


int main() {
	sys_beep(300,5);
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
