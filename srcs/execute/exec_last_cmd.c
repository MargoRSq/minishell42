/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_last_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:41:46 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/12 18:41:47 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_last_cmd(t_list *envlst, t_cmd *cmd, t_fd *fds, int fl)
{
	int	pid;

	if (fl % 2 != 0)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fds->fd2[0], STDIN_FILENO);
			close(fds->fd2[0]);
			bin_run_multi(envlst, cmd, fds, fl);
		}
	}
	else
	{
		pid = fork();
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
