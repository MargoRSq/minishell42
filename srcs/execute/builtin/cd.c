/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:57 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/10 18:29:15 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*go_oldpwd(t_list *envlst)
{
	char	*old_pwd;
	char	*new_path;

	old_pwd = get_env_value("OLDPWD", envlst);
	if (!old_pwd)
		return (error_msg_return_null(MSG_ERR_CD_OLDPWD, NULL,
				oldpwd_error, 0));
	if (chdir(old_pwd) == -1)
		return (error_msg_return_null(MSG_SYSCALL_ERR_CHDIR, NULL,
				chdir_error, 0));
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (error_msg_return_null(MSG_SYSCALL_ERR_GETCWD, NULL,
				cwd_error, 1));
	return (new_path);
}

static char	*go_home(t_list *envlst)
{
	char	*home;
	char	*new_path;

	home = get_env_value("HOME", envlst);
	if (!home)
		return (error_msg_return_null(MSG_ERR_HOME, NULL, home_error, 0));
	if (chdir(home) == -1)
		return (error_msg_return_null(MSG_SYSCALL_ERR_CHDIR, NULL,
				chdir_error, 0));
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (error_msg_return_null(MSG_SYSCALL_ERR_GETCWD, NULL,
				cwd_error, 1));
	return (new_path);
}

char	*form_path_to_go(char **cmd_argv, t_list *envlst)
{
	char		*path;
	char		*tmp;
	char		*help_getcwd;

	if (!ft_strcmp(cmd_argv[1], "..") || cmd_argv[1][0] == '/')
		path = ft_strdup(cmd_argv[1]);
	else
	{
		help_getcwd = getcwd(NULL, 0);
		if (!help_getcwd)
			return (error_msg_return_null(MSG_SYSCALL_ERR_GETCWD, NULL,
					cwd_error, 1));
		tmp = ft_strjoin(help_getcwd, "/");
		free(help_getcwd);
		if (!tmp)
			return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
					malloc_error, 1));
		path = ft_strjoin(tmp, cmd_argv[1]);
		free(tmp);
	}
	if (!path)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	return (path);
}

static char	*go_cd_argv(char **cmd_argv, t_list *envlst)
{
	char	*path_to_go;
	char	*new_path;
	char	*tmp;

	path_to_go = form_path_to_go(cmd_argv, envlst);
	if (!path_to_go)
		return (NULL);
	if (chdir(path_to_go) == -1)
	{
		free(path_to_go);
		return (error_msg_return_null(MSG_SYSCALL_ERR_CHDIR, cmd_argv[1],
				chdir_error, 0));
	}
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		free(path_to_go);
		return (error_msg_return_null(MSG_SYSCALL_ERR_GETCWD, NULL,
				cwd_error, 1));
	}
	free(path_to_go);
	return (new_path);
}

void	execute_cd(t_list *envlst, char **cmd_argv)
{
	char	*pwd_to_change;
	char	*new_path;

	pwd_to_change = getcwd(NULL, 0);
	if (!pwd_to_change)
		return (error_msg_return_void(MSG_SYSCALL_ERR_GETCWD, NULL,
				cwd_error, 1));
	if (!cmd_argv[1] || !ft_strcmp(cmd_argv[1], "~"))
		new_path = go_home(envlst);
	else if (!ft_strcmp(cmd_argv[1], "-"))
		new_path = go_oldpwd(envlst);
	else if (cmd_argv[1])
		new_path = go_cd_argv(cmd_argv, envlst);
	if (!new_path)
	{
		free(pwd_to_change);
		return ;
	}
	change_or_append(envlst, ft_strdup("OLDPWD"), ft_strdup(pwd_to_change));
	change_or_append(envlst, ft_strdup("PWD"), ft_strdup(new_path));
	free(new_path);
	free(pwd_to_change);
}
