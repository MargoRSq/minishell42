#include "minishell.h"

void	exec_last_cmd(t_env *env, t_cmd *cmd, t_fd *fds)
{
	printf("{cmd=%s, args=%d, in=%d, out=%d}\n",
		   cmd->argv[0], cmd->counter.words - 1, cmd->counter.in, cmd->counter
				   .out);
	int pid = fork();
	if (pid == 0)
	{
		write(1, "child3", 7);
		write(1, "\n", 1);
		dup2(fds->fd2[0], STDIN_FILENO);
		close(fds->fd2[0]);
		exit(0);
//		execlp("ls", "ls", NULL);
//		execve(get_cmd(env, cmd->argv[0]), cmd->argv,
//				   envlst_to_arr(env));
	}
}