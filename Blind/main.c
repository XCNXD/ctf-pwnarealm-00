	#include <stdio.h>
	#include <stdlib.h>
	#include <signal.h>
	#include <string.h>
	#include <unistd.h>
	#include <fcntl.h>


	long int ft_str_is_printable(char *str)
	{
		int	i;

		i = 0;
		while (str[i] != 0)
		{
			if (str[i] < ' ' || str [i] > '~')
			{
				return (long int)(str+i);
			}
			i++;
		}
		return 0;
	}

	char *cmd;
	int fd;
	void segfault_handler(int sig, siginfo_t *info, void *ucontext) {
		(void)ucontext;
		printf("Fauly");
		char* escape = (char *)ft_str_is_printable(cmd);
		printf("Esacpe");
		if(escape != 0){
			*escape = '\x00';
		}
		// dup2(fd, 1);
		write(2, "dup", 3);
		system(cmd);
		printf(2, "sys", 3);
		close(fd);
		exit(1);
	}

	int main() {
		struct sigaction sa;
		memset(&sa, 0, sizeof(sa));
		sa.sa_sigaction = segfault_handler;
		sa.sa_flags = SA_SIGINFO;
		if (sigaction(SIGSEGV, &sa, NULL) == -1) {
			perror("sigaction");
			exit(EXIT_FAILURE);
		}
		
		fd = open("/dev/null", O_WRONLY);
		if(fd == -1)
		{
			perror("open /dev/null");
			return -1;
		}

		char x[0x1000];
		setbuf(stdin, 0);
		setbuf(stdout, 0);
		setbuf(stderr, 0);

		puts("Anything?");
		read(0, x, 0x2000);
		araiwa = malloc(0x100);
		if(araiwa == NULL)
		{
			puts("Fail");
			return -1;
		}
		if(strlen(x) > 0x1000){
			strcpy(araiwa, x+0x1000);
		}
		return 0;
	}
