/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:43:03 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/15 14:34:49 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bin_run_multi(t_list *envlst, t_cmd *cmd, t_fd *fds, int fl)
{
	char	*bin;

	replace_fds_start(cmd, fds);
	if (check_builtin(cmd->argv[0]))
		try_builtin(cmd, &envlst);
	else
	{
		bin = get_cmd(envlst, cmd->argv[0]);
		if (bin)
			execve(bin, cmd->argv, envlst_to_arr(envlst));
		error_msg_return_void(MSG_ERR_CMD_NF, cmd->argv[0],
			execve_error, 0);
		if (fl % 2 != 0)
			dup2(STDOUT_FILENO, fds->fd1[0]);
		else
			dup2(STDOUT_FILENO, fds->fd2[0]);
	}
	replace_fds_finish(cmd, fds);
	exit(1);
}

void	exec_first_cmd(t_list *envlst, t_cmd *cmd, t_fd *fds)
{
	int	pid;

	if (pipe(fds->fd1) == -1)
		error_msg_return_void(MSG_SYSTEM_ERR_PIPE, NULL, pipe_error, 1);
	pid = fork();
	if (pid == -1)
		error_msg_return_void(MSG_SYSTEM_ERR_FORK, NULL, fork_error, 1);
	if (pid == 0)
	{
		dup2(fds->fd1[1], STDOUT_FILENO);
		close(fds->fd1[0]);
		close(fds->fd1[1]);
		bin_run_multi(envlst, cmd, fds, 1);
	}
	close(fds->fd1[1]);
}
