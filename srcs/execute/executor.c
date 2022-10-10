/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:34:21 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 18:34:28 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_builtin(t_cmd *cmd, t_list **envlst)
{
	if (!ft_strcmp(cmd->argv[0], "cd"))
		execute_cd(*envlst, cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		execute_echo(cmd->argv);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		execute_pwd(*envlst);
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
	t_cmd	*command;
	t_list	*next;

	next = cmdlst->next;
	if (cmdlst->content)
		command = (t_cmd *)(cmdlst->content);
	if (next == NULL)
		only_parent_process(envlst, cmdlst);
	else
		multi_pipe_process(envlst, cmdlst);
}
