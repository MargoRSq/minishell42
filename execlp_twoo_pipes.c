#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
	int fd[3][2];
	int i;
	for (i = 0; i < 3; i++)
	{
		if (pipe(fd[i]) < 0)
			return 1;
	}
	int pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		int x;
		if (read(fd[0][0], &x, sizeof(int)) < 0)
			return (3);
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) < 0)
			return (4);
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return (5);
	if (pid2 == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int y;
		if (read(fd[1][0], &y, sizeof(int)) < 0)
			return (6);
		y += 5;
		if (write(fd[2][1], &y, sizeof(int)) < 0)
			return (7);
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	//parent proc
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	int z;
	printf("Put the number->\n");
	scanf("%d", &z);
	if (write(fd[0][1], &z, sizeof(int)) < 0)
		return (8);
	if (read(fd[2][0], &z, sizeof(int)) < 0)
		return (9);
	printf("result is: %d\n", z);
	close(fd[0][1]);
	close(fd[2][0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}