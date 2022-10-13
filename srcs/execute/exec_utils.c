/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:40:07 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/13 16:55:53 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_fds_start(t_cmd *cmd, t_fd *fds)
{
	if (cmd->infile)
	{
		fds->in_fd = open(cmd->infile->name, O_RDONLY);
		fds->in_tmp = dup(STDIN_FILENO);
		dup2(fds->in_fd, STDIN_FILENO);
	}
	if (cmd->outfile)
	{
		if (cmd->outfile->type == r_out)
		{
			fds->out_fd = open(cmd->outfile->name, O_RDWR | O_CREAT,
					S_IWUSR | S_IRUSR);
		}
		else
			fds->out_fd = open(cmd->outfile->name, O_WRONLY | O_APPEND
					| O_CREAT, 0664);
		fds->out_tmp = dup(STDOUT_FILENO);
		dup2(fds->out_fd, STDOUT_FILENO);
	}
}

void	replace_fds_finish(t_cmd *cmd, t_fd *fds)
{
	if (cmd->infile)
	{
		dup2(fds->in_tmp, STDIN_FILENO);
		close(fds->in_fd);
	}
	if (cmd->outfile)
	{
		dup2(fds->out_tmp, STDOUT_FILENO);
		close(fds->out_fd);
	}
}
