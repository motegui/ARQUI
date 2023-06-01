/* sampleCodeModule.c */
#include <stdint.h>
#include <time_driver.h>
#include <user_syscalls.h>
#include <functions.h>
#include <exceptionTester.h>

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
	sys_write("REGISTERS TEST", GREEN);
	sys_write(": to check the correct loading of registers ", WHITE);
	enter();
	sys_write("REGISTERS", GREEN);
	sys_write(": to print register status", WHITE);
	enter();
	sys_write("DIVIDE BY ZERO", GREEN);
	sys_write(": to trigger divide by zero exception", WHITE);
	enter();
	sys_write("INVALID OPERATION", GREEN);
	sys_write(": to trigger invalid operation exception ", WHITE);
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
	else if(strcmp(buffer, "REGISTERS TEST")==0){
		print("Registers should have the next values");
		enter();
		print("RAX:2");
		enter();
		print("RBX:2");
		enter();
		print("RCX:2");
		enter();
		print("RDX:6");
		enter();
		print("RSI:8");
		enter();
		print("RDI:1");
		enter();
		print("RBP:1");
		enter();
		print("R8:AN HEXA NUMBER");
		enter();
		print("R9:9");
		enter();
		print("R10:A");
		enter();
		print("R11:B");
		enter();
		print("R12:C");
		enter();
		print("R13:D");
		enter();
		print("R14:E");
		enter();
		print("R15:F");
		enter();
		print("Press 'CTRL' now");
		enter();
		testRegs();
		enter();
	}
	else if(strcmp(buffer, "DIVIDE BY ZERO")==0){
		divisionTester();
	
	}
	else if(strcmp(buffer, "INVALID OPERATION")==0){
		invalidOpTester();
	
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