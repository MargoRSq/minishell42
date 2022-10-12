/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_parent_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:42:01 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/12 18:42:55 by svyatoslav       ###   ########.fr       */
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

char	*get_path(t_list *envlst)
{
	char	*result;
	char	*ways;
	char	*ways_with_dot;
	char	*cur_dir;

	ways = NULL;
	ways_with_dot = NULL;
	cur_dir = NULL;
	result = NULL;
	ways = get_env_value("PATH", envlst);
	ways_with_dot = ft_strjoin(ways, ":");
	cur_dir = getcwd(NULL, 0);
	result = ft_strjoin(ways_with_dot, cur_dir);
	free(ways_with_dot);
	free(cur_dir);
	return (result);
}

char	*get_cmd(t_list *envlst, char *cmd)
{
	char	*command;
	char	*ways;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	ways = get_path(envlst);
	paths = ft_split(ways, ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(command, X_OK))
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	bin_run(t_list **envlst, t_list *cmdlst, t_fd *fds)
{
	int		fd;
	char	*bin;
	t_cmd	*cmd;

	cmd = cmdlst->content;
	fd = fork();
	if (fd == 0)
	{
		replace_fds_start(cmd, fds);
		bin = get_cmd(*envlst, cmd->argv[0]);
		if (bin)
			execve(bin, cmd->argv, envlst_to_arr(*envlst));
		else
		{
			replace_fds_finish(cmd, fds);
			return (error_msg_return_void(MSG_ERR_CMD_NF, cmd->argv[0],
					execve_error, 0));
		}
	}
	else
		wait(0);
}

void	only_parent_process(t_list **envlst, t_list *cmdlst, t_fd *fds)
{
	t_cmd			*cmd;

	cmd = cmdlst->content;
	if (cmd->argv[0])
	{
		if (check_builtin(cmd->argv[0]))
		{
			replace_fds_start(cmd, fds);
			try_builtin(cmd, envlst);
			replace_fds_finish(cmd, fds);
		}
		else
			bin_run(envlst, cmdlst, fds);
	}
}
