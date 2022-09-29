#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(void)
{
	int fd[2];
	int fd1[2];
	int pid1;
	int pid2;
	int pid3;

	pipe(fd);
	pipe(fd1);
	pid1 = fork();
	if (pid1 == 0)
	{
		printf("print a number ->\n");
		int x;
		close(fd[0]);
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
		exit(0);
	}

	pid2 = fork();
	if (pid2 == 0)
	{
		int y;
		close(fd[1]);
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("integer is: %d\n", y);
		y *= 2;
		close(fd1[0]);
		write(fd1[1], &y, sizeof(int));
		close(fd1[1]);
		exit(0);
	}

	pid3 = fork();
	if (pid3 == 0)
	{
		int z;
		close(fd1[1]);
		read(fd1[0], &z, sizeof(int));
		close(fd1[0]);
		printf("integer is: %d\n", z);
		exit(0);
	}

		while (wait(0) != -1)
			;
		printf("parent finish\n");
	}
//}