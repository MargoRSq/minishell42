
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int ac, char**av, char**envp)
{

	char *input;
	char *output;
	input = malloc(1000);
	read(STDIN_FILENO, input, 2);
	output = input;
	write(STDOUT_FILENO, output, 2);
	return(1);
}