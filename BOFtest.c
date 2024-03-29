#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int foo(char* bar);

int main(int argc, char** argv)
{
	printf(" %s", "CEG");
	foo(argv[1]);
	printf(" %s", "44246424");
	return 0;
}
int foo(char* bar)
{
	char c[12];
	strcpy(c, bar);
        return 0; 
}
