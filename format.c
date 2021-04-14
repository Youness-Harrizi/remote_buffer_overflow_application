#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char useful_string[16]= "/bin/bash";
/* gcc format.c -o format -fno-stack-protector -m32*/
void center(void)
{
	system("whoami");
  char code[128];
  printf("Enter secret code !\nCode: ");
  gets(code);			//take input
  printf("Entered Command center with code > %s .\n",code);

}


int main()

{	
		system("id");
		printf("useful_string:%p",useful_string);
		printf("address of printf :%p",printf);
		printf("address of system :%p",system);
	char name[64];
	setvbuf(stdin, 0, 2, 0);		//no buffering in stdin and stdout
	setvbuf(stdout, 0, 2, 0);
	memset(name, 0, sizeof(name));		//fill name buffer with null bytes
	printf("What is your name?\nName: ");
	read(0, name, 64);			//read 64 bytes from stdin(0) to name
	printf("Hello "); printf(name);
	center();				//call center function
	return 0;
}	