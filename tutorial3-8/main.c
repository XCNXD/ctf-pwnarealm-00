#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <errno.h>
// gcc -no-pie -fstack-protector -Wl,-z,relro,-z,now main.c -o challx
#define MAX_MESSAGES 8

typedef struct Message {
    size_t size;
    char *content;
} Message;

void reward() {
    system("/bin/sh");
}

void store_message(Message **messages) {
    unsigned int index;
    printf("Index to store message: ");
    scanf("%u", &index);

    if (index >= MAX_MESSAGES || messages[index] != NULL) {
        puts("Invalid or already occupied index.");
        return;
    }

    messages[index] = malloc(0x30); // Allocates 0x30 bytes
    if (!messages[index]) {
        puts("Memory allocation failed.");
        return;
    }

    printf("Enter size of message (max 64): ");
    scanf("%zu", &messages[index]->size);

    if (messages[index]->size > 0x40) {
        puts("Size too large.");
        free(messages[index]);
        messages[index] = NULL;
        return;
    }

    messages[index]->content = malloc(messages[index]->size);
    if (!messages[index]->content) {
        puts("Memory allocation failed.");
        free(messages[index]);
        messages[index] = NULL;
        return;
    }

    printf("Enter your message: ");
    read(0, messages[index]->content, messages[index]->size);
    puts("Message stored!");
}

void delete_message(Message **messages) {
    unsigned int index;
    printf("Index to delete message: ");
    scanf("%u", &index);

    if (index >= MAX_MESSAGES || messages[index] == NULL) {
        puts("Invalid index.");
        return;
    }

    free(messages[index]->content);
    free(messages[index]);
    puts("Message deleted!");
}

void read_message(Message **messages) {
    unsigned int index;
    printf("Index to read message: ");
    scanf("%u", &index);

    if (index >= MAX_MESSAGES || messages[index] == NULL) {
        puts("Invalid index.");
        return;
    }

    printf("Message at index %u: %s\n", index, messages[index]->content);
}

void edit_message(Message **messages) {
    unsigned int index;
    printf("Index to edit message: ");
    scanf("%u", &index);

    if (index >= MAX_MESSAGES || messages[index] == NULL) {
        puts("Invalid index.");
        return;
    }

	char text[48];
    printf("Enter new message: ");
    ssize_t bytes_read = read(0, text, 48);
	// char text[messages[index]->size];
	// scanf("%s", text);
	// printf("Error: %d\n", memcpy(messages[index]->content, text, messages[index]->size));
	if (bytes_read < 0) {
		switch (errno) {
			case EINTR:
				printf("Read was interrupted by a signal.\n");
				break;
			case EBADF:
				printf("Invalid file descriptor passed to read().\n");
				break;
			case EINVAL:
				printf("Invalid argument passed to read().\n");
				break;
			default:
				printf("Unknown error occurred: %d\n", errno);
				break;
    	}
	}
	int i = 0;
	while(i < bytes_read)
	{
		messages[index]->content[i] = text[i];
		i++;
	}
	printf("Write to: %lx with: %s Size: %d\n", messages[index]->content, messages[index]->content, bytes_read); 
    puts("Message updated!");
}

int main() {
	// mallopt(M_MXFAST, 0);

	// void *ptrs[7];

	// for (int i=0; i<7; i++) {
	// 	ptrs[i] = malloc(0x30);
	// }
	// for (int i=0; i<7; i++) {
	// 	free(ptrs[i]);
	// }
	char Unsed[10];
    Message *messages[MAX_MESSAGES] = {0};
    unsigned int input;

	setvbuf(stderr, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stdin, 0LL, 1, 0LL);

    printf("Welcome to the Vulnerable Messenger!\n");
    printf("Message card store at address: %p\n", (void*)messages);
    while (1) {
        printf("\nMenu:\n");
        printf("0 - Store a message\n");
        printf("1 - Read a message\n");
        printf("2 - Delete a message\n");
        printf("3 - Edit a message\n");
        printf("4 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &input);

        switch (input) {
            case 0:
                store_message(messages);
                break;
            case 1:
                read_message(messages);
                break;
            case 2:
                delete_message(messages);
                break;
            case 3:
                edit_message(messages);
                break;
            case 4:
                puts("Exit...");
                return 0;
            default:
                puts("Invalid option.");
                exit(-1);
        }
    }
}
