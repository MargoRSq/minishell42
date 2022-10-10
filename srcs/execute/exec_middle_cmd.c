#include "minishell.h"

void	exec_middle_cmd(t_list *env, t_cmd *cmd, t_fd *fds, int fl)
{
	int	pid;

	if (fl % 2 == 0)//we are in the even child
	{
		if (pipe(fds->fd2) == -1)
			error_msg_return_void(MSG_SYSTEM_ERR_PIPE, NULL, pipe_error, 1);
		pid = fork();
		if (pid == -1)
			error_msg_return_void(MSG_SYSTEM_ERR_FORK, NULL, fork_error, 1);
		else if (pid == 0)
		{
			dup2(fds->fd1[0], STDIN_FILENO);
			dup2(fds->fd2[1], STDOUT_FILENO);
			close(fds->fd1[0]);
			close(fds->fd2[1]);
			execve(get_cmd(env, cmd->argv[0]), cmd->argv,
				   envlst_to_arr(env));
			error_msg_return_void(MSG_ERR_CMD_NF, cmd->argv[0],
								  execve_error, 0);
//			exit(0);
		}
		close(fds->fd1[0]);
		close(fds->fd2[1]);
	}
	else//odd child
	{
		if (pipe(fds->fd1) == -1)
			error_msg_return_void(MSG_SYSTEM_ERR_PIPE, NULL, pipe_error, 1);
		pid = fork();
		if (pid == -1)
			error_msg_return_void(MSG_SYSTEM_ERR_FORK, NULL, fork_error, 1);
		else if (pid == 0)
		{
			dup2(fds->fd2[0], STDIN_FILENO);
			dup2(fds->fd1[1], STDOUT_FILENO);
			close(fds->fd2[0]);
			close(fds->fd1[1]);
			execve(get_cmd(env, cmd->argv[0]), cmd->argv,
				   envlst_to_arr(env));
			error_msg_return_void(MSG_ERR_CMD_NF, cmd->argv[0],
										  execve_error, 0);
//			exit(0);
		}
		close(fds->fd2[0]);
		close(fds->fd1[1]);
	}
}