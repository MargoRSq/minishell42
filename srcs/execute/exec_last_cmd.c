#include "minishell.h"

void	exec_last_cmd(t_list *env, t_cmd *cmd, t_fd *fds, int fl)
{
	if (fl % 2 != 0)//odd child
	{
		int pid = fork();
		if (pid == 0)
		{
			dup2(fds->fd2[0], STDIN_FILENO);
			close(fds->fd2[0]);
			execve(get_cmd(env, cmd->argv[0]), cmd->argv,
				   envlst_to_arr(env));
		}
	}
	else
	{
		int pid = fork();
		if (pid == 0)
		{
			dup2(fds->fd1[0], STDIN_FILENO);
			close(fds->fd1[0]);
			execve(get_cmd(env, cmd->argv[0]), cmd->argv,
				   envlst_to_arr(env));
		}	}
}