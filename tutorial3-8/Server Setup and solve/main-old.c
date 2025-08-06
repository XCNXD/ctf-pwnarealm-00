#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Messenger
#define arr_size 10

void shell()
{
	system("/bin/sh");
}

void store_message(char** MessageBox)
{
	char input[48];
	unsigned int i;
	puts("Where do you want to store the message");
	scanf("%u", &i);
	char* temp;
	puts("Say something: ");
	scanf("%47s", input);
	if (i < arr_size){
		if (MessageBox[i] == 0)
		{
			temp = calloc(1, 48);
			printf("Sucessfull Allocate at %x", temp);
			strcpy(temp, input);
			MessageBox[i] = temp;
		}
		else
		{
			printf("Found Allocated! %x\n", MessageBox[i]);
			strcpy(MessageBox[i], input);
		}
	}
}

void read_message(char** MessageBox)
{
	unsigned int i;
	puts("where do you want to read");
	scanf("%u", &i);
	if (i < arr_size){
		printf("Message at index %u: %s\n", i, MessageBox[i]);
		free(MessageBox[i]);
	}
}

void setup()
{
	setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stdin, 0LL, 1, 0LL);
}

void list(char **MessageBox)
{
	for (int i = 0; i < arr_size; i++)
	{
		if (MessageBox[i])
		{
			printf("Malloc : %lx\n",MessageBox[i]);
		}
	}
}

int main() //gcc -no-pie -fno-stack-protector main.c -o challx
{
	int *MessageBox[arr_size] = {0};
	unsigned int input;
	void *ptrs[7];

	for (int i=0; i<7; i++) {
		ptrs[i] = malloc(0x30);
	}
	for (int i=0; i<7; i++) {
		free(ptrs[i]);
	}
    printf("Welcome to the Messenger Box\n");
    printf("Message card store at address: %p\n", (void*)MessageBox);
	while (1){
		printf("\nMenu:\n");
        printf("0 - Store a message\n");
        printf("1 - Read a message\n");
        printf("2 - Exit\n");
        printf("Enter your choice: ");
		scanf("%d", &input);
		switch (input) {
			case 0:
				store_message((char **)MessageBox);
				break;
			case 1:
				read_message((char **)MessageBox);
				break;
			case 2:
				puts("Exit...");
				return 0;
			case 3:
				list((char **)MessageBox);
				break;
			default: 
				puts("That's not in the options...");
				exit(-1);
		}
	}
}