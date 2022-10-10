#include "minishell.h"

void	exec_last_cmd(t_list *envlst, t_cmd *cmd, t_fd *fds, int fl)
{
	if (fl % 2 != 0)//odd child
	{
		int pid = fork();
		if (pid == 0)
		{
			dup2(fds->fd2[0], STDIN_FILENO);
			close(fds->fd2[0]);
			bin_run_multi(envlst, cmd, fds, fl);
		}
	}
	else
	{
		int pid = fork();
		if (pid == 0)
		{
			dup2(fds->fd1[0], STDIN_FILENO);
			close(fds->fd1[0]);
			bin_run_multi(envlst, cmd, fds, fl);
		}
		else
			wait(0);
	}
}