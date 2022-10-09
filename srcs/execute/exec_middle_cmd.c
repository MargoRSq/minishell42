#include "minishell.h"

void	exec_middle_cmd(t_env *env, t_cmd *cmd, t_fd *fds)
{
	printf("{cmd=%s, args=%d, in=%d, out=%d}\n",
		   cmd->argv[0], cmd->counter.words - 1, cmd->counter.in, cmd->counter.
		   out);
	int	pid;

	pid = fork();
	if (pid == -1)
		error_msg_return_void(MSG_SYSTEM_ERR_FORK, NULL, fork_error, 1);
	else if (pid == 0)
	{
		write(1, "child2", 7);
		write(1, "\n", 1);
		dup2(fds->fd1[0], STDIN_FILENO);
		dup2(fds->fd2[1], STDOUT_FILENO);
		close(fds->fd1[0]);
		close(fds->fd2[1]);
		// execlp("ls", "ls", NULL);
		execve(get_cmd(env, cmd->argv[0]), cmd->argv,
				   envlst_to_arr(env));
	}
	close(fds->fd1[0]);
	close(fds->fd2[1]);

}