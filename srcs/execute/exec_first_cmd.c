#include "minishell.h"

void	exec_first_cmd(t_env *env, t_cmd *cmd, t_fd *fds)
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
		write(1, "child", 6);
		write(1, "\n", 1);
		dup2(fds->fd1[1], STDOUT_FILENO);
		close(fds->fd1[0]);
		close(fds->fd1[1]);
		if (check_builtin(cmd->argv[0]))
			try_builtin(cmd, &env);
		else
		{
			execve(get_cmd(env, cmd->argv[0]), cmd->argv,
				   envlst_to_arr(env));
		}
	}
	close(fds->fd1[1]);
}