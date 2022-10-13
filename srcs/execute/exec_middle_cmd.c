/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_middle_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:43:27 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/13 15:45:30 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_in_child(t_run *run, int *read, int *write)
{
	int	pid;

	if (pipe(write) == -1)
		error_msg_return_void(MSG_SYSTEM_ERR_PIPE, NULL, pipe_error, 1);
	pid = fork();
	if (pid == -1)
		error_msg_return_void(MSG_SYSTEM_ERR_FORK, NULL, fork_error, 1);
	else if (pid == 0)
	{
		dup2(read[0], STDIN_FILENO);
		dup2(write[1], STDOUT_FILENO);
		close(read[0]);
		close(write[1]);
		bin_run_multi(run->envlst, run->cmd, run->fds, run->flag);
	}
	close(read[0]);
	close(write[1]);
}

void	exec_middle_cmd(t_list *envlst, t_cmd *cmd, t_fd *fds, int fl)
{
	t_run	run;

	run = (t_run){.cmd = cmd, .envlst = envlst, .fds = fds, .flag = fl};
	if (fl % 2 == 0)
	{
		run_in_child(&run, fds->fd1, fds->fd2);
		close(fds->fd1[0]);
	}
	else
	{
		run_in_child(&run, fds->fd2, fds->fd1);
		close(fds->fd2[0]);
	}
}
