#include "minishell.h"

void	exec_first_cmd(t_env *env, t_cmd *cmd, int *fd)
{
	printf("{cmd=%s, args=%d, in=%d, out=%d}\n",
		   cmd->argv[0], cmd->counter.words - 1, cmd->counter.in, cmd->counter
		   .out);
	int	pid;

	pid = fork();
	if (pid == -1)
		error_msg_return_void(MSG_SYSTEM_ERR_FORK, NULL, fork_error, 1);
	else if (pid == 0)
	{
		int x = scanf(STDIN_FILENO, &x, sizeof(int));
		close(fd[0]);
		dup2(STDOUT_FILENO, fd[1]);
		close(fd[1]);



	}
}