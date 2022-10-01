/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:57 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/28 21:48:23 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_old_pwd(t_env *env, char *old_path)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp("OLDPWD", tmp->key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(old_path);
			if (!tmp->value)
				return (error_msg_return_void(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
			return ;
		}
		tmp = tmp->next;
	}
	append_env_var(env, ft_strdup("OLDPWD"), ft_strdup(old_path));
}

void	update_pwd(t_env *env, const char *new_path)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp("PWD", tmp->key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_path);
			if (!tmp->value)
				return (error_msg_return_void(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
			return ;
		}
		tmp = tmp->next;
	}
	append_env_var(env, ft_strdup("PWD"), ft_strdup(new_path));
}

static const char	*go_oldpwd(t_env *env) //not working
{
	const char	*old_pwd;

	old_pwd = get_env_value("OLDPWD", env);
	if (!old_pwd)
		return (error_msg_return_null(MSG_ERR_CD_OLDPWD, NULL, oldpwd_error, 0));
	if (chdir(old_pwd) == -1)
		return (error_msg_return_null(MSG_SYSCALL_ERR_CHDIR, NULL, chdir_error, 1));
	return (old_pwd);
}

static const char	*go_home(t_env *env) //in bash even if HOME unset goes home
{
	const char	*new_path;

	new_path = get_env_value("HOME", env);
	if (!new_path)
		return (error_msg_return_null(MSG_ERR_HOME, NULL, home_error, 0));
	if (chdir(new_path) == -1)
		return (error_msg_return_null(MSG_SYSCALL_ERR_CHDIR, NULL, chdir_error, 1));
	return (new_path);
}

char	*form_path_to_go(char **cmd_argv, t_env *env)
{
	char		*path;
	char		*tmp;

	if (!ft_strcmp(cmd_argv[1], "..") || cmd_argv[1][0] == '/')
		path = ft_strdup(cmd_argv[1]);
	else
	{
		tmp = ft_strjoin(get_cur_dir(env), "/");
		if (!tmp)
			return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
		path = ft_strjoin(tmp, cmd_argv[1]);
		free(tmp);
	}
	if (!path)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
	return (path);
}

static const char	*go_cd_argv(char **cmd_argv, t_env *env)
{
	char		*path_to_go;
	const char	*new_path;
	char		*tmp;

	path_to_go = form_path_to_go(cmd_argv, env);
	if (!path_to_go)
		return (NULL);
	if (chdir(path_to_go) == -1)
	{
		free(path_to_go);
		return (error_msg_return_null(MSG_SYSCALL_ERR_CHDIR, cmd_argv[1], chdir_error, 0));
	}
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		free(path_to_go);
		return (error_msg_return_null(MSG_SYSCALL_ERR_GETCWD, NULL, cwd_error, 1));
	}
	return (new_path);
}

void	execute_cd(t_env *env, char **cmd_argv)
{
	char		*pwd_to_change;
	const char	*new_path;

	pwd_to_change = get_cur_dir(env);
	if (!pwd_to_change)
		return (error_msg_return_void(MSG_SYSCALL_ERR_GETCWD, NULL, cwd_error, 1));
	if (!cmd_argv[1] || !ft_strcmp(cmd_argv[1], "~"))
		new_path = go_home(env);
	else if (!ft_strcmp(cmd_argv[1], "-"))
		new_path = go_oldpwd(env);
	else if (cmd_argv[1])
		new_path = go_cd_argv(cmd_argv, env);
	if (!new_path)
		return ;
	update_old_pwd(env, pwd_to_change);
	update_pwd(env, new_path);
}
