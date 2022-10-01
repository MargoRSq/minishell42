#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
	int fd[2];
	if (pipe(fd) == -1)
		perror("pipe failed\n");
	int pid1 = fork();
	if (pid1 == 0)
	{
		printf("child1\n");
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("ls", "ls", "-la", NULL);
	}
	int pid2 = fork();
	if (pid2 == 0)
	{
		printf("child2\n");
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("wc", "wc", "-l", NULL);
	}
	close(fd[0]);//recommended to close all pipes fd after
	close(fd[1]);//finishing all work to continue the parent proc
	waitpid(pid1, NULL, 0);//waiting for all children proc
	waitpid(pid2, NULL, 0);
	printf("parent finish\n");

	return (0);
}







//int	main(void)
//{
//	int fd[2];
//	int fd1[2];
//	int pid1;
//	int pid2;
//	int pid3;
//
//	pipe(fd);
//	pipe(fd1);
//	pid1 = fork();
//	if (pid1 == 0)
//	{
//		printf("print a number ->\n");
//		int x;
//		close(fd[0]);
//		scanf("%d", &x);
//		write(fd[1], &x, sizeof(int));
//		close(fd[1]);
//		exit(0);
//	}
//
//	pid2 = fork();
//	if (pid2 == 0)
//	{
//		int y;
//		close(fd[1]);
//		read(fd[0], &y, sizeof(int));
//		close(fd[0]);
//		printf("integer is: %d\n", y);
//		y *= 2;
//		close(fd1[0]);
//		write(fd1[1], &y, sizeof(int));
//		close(fd1[1]);
//		exit(0);
//	}
//
//	pid3 = fork();
//	if (pid3 == 0)
//	{
//		int z;
//		close(fd1[1]);
//		read(fd1[0], &z, sizeof(int));
//		close(fd1[0]);
//		printf("integer is: %d\n", z);
//		exit(0);
//	}
//
//	while (wait(0) != -1)
//		;
//	printf("parent finish\n");
//}
