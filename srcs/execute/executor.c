/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:34:21 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/12 21:31:51 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *cmd)
{
	if (cmd)
		ft_tolower(cmd);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

int	try_builtin(t_cmd *cmd, t_list **envlst)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		execute_cd(*envlst, cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		execute_echo(cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		execute_pwd();
	else if (!ft_strcmp(cmd->argv[0], "env"))
		execute_env(*envlst, cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		execute_unset(envlst, cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		execute_exit(cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		execute_export(*envlst, cmd->argv);
	return (1);
}

void	execute(t_list **envlst, t_list *cmdlst)
{
	t_list	*next;
	t_fd	fds;

	next = cmdlst->next;
	if (next == NULL)
		only_parent_process(envlst, cmdlst, &fds);
	else
		multi_pipe_process(envlst, cmdlst, &fds);
}
