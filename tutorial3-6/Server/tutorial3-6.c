/*
	oob -> mprotect
*/

#include <stdio.h>
#include <stdlib.h>

void vuln(char* buffer)
{
	int size;
	if (scanf("%d%*c", &size) != 1)
	{
		puts("uhh??");
		exit(0);	
	}

	long **pointer = (long **)(8 * size + (long)buffer);
  	*pointer = (long *)calloc(1, 128);
	char* result = fgets((char *)(*pointer), 128, stdin);

 	if ( !result )
  	{
		puts("wtf??");
		exit(0);
	}
}
int main() //gcc tutorial3-6 -o challx -static -fno-stack-protector
{
	char text[32];
	vuln(text);
}