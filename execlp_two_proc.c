#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int fd1[2];
	int fd2[2];

	if (pipe(fd1) == -1)
		perror("pipe failed\n");
	int pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fd1[1], STDOUT_FILENO);
		close(fd1[0]);
		close(fd1[1]);
		execlp("ls", "ls", "-la", NULL);
	}
	close(fd1[1]);
	pipe(fd2);
	int pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd1[0], STDIN_FILENO);
		dup2(fd2[1], STDOUT_FILENO);
		close(fd1[0]);
		close(fd2[1]);
		execlp("wc", "wc", "-l", NULL);
	}
	close(fd1[0]);//recommended to close all pipes fd after
	close(fd2[1]);//finishing all work to continue the parent proc
	int pid3 = fork();
	if (pid3 == 0)
	{
		dup2(fd2[0], STDIN_FILENO);
		close(fd2[0]);
		execlp("wc", "wc", "-l", NULL);
	}
	while (wait(0) != -1)//waiting for all children proc
		;
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
