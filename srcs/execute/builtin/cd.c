/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:57 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/26 20:28:35 by ptoshiko         ###   ########.fr       */
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
		return (NULL);
	if (chdir(old_pwd) == -1)
		return (NULL);
	return (old_pwd);
}

static const char	*go_home(t_env *env)
{
	const char	*new_path;

	new_path = get_env_value("HOME", env);
	if (!new_path)
	{
		error_msg_return_void(MSG_ERR_HOME, "", 4, 1);
		return (NULL);
	}
	if (chdir(new_path) == -1)
	{
		error_msg_return_void(MSG_ERR_HOME, "", 4, 1);
		return (NULL);
	}
	return (new_path);
}

static const char	*go_cd_argv(char **cmd_argv, t_env *env)
{
	char		*path_to_go;
	const char	*new_path;
	char		*tmp;

	if (!ft_strcmp(cmd_argv[0], "..") || cmd_argv[0][0] == '/')
		path_to_go = ft_strdup(cmd_argv[0]);
	else
	{
		tmp = ft_strjoin(get_cur_dir(env), "/");
		path_to_go = ft_strjoin(tmp, cmd_argv[0]);
		free(tmp);
	}
	if (chdir(path_to_go) == -1)
	{
		error_msg_return_void(MSG_ERR_CD_NO, cmd_argv[0], 1, 0);
		free(path_to_go);
		return (NULL);
	}
	new_path = getcwd(NULL, 0);
	free(path_to_go);
	return (new_path);
}

void	execute_cd(t_env *env, char **cmd_argv)
{
	char		*pwd_to_change;
	const char	*new_path;

	pwd_to_change = get_cur_dir(env);
	if (!cmd_argv[0] || !ft_strcmp(cmd_argv[0], "~"))
		new_path = go_home(env);
	else if (!ft_strcmp(cmd_argv[0], "-"))
		new_path = go_oldpwd(env);
	else if (cmd_argv[0])
		new_path = go_cd_argv(cmd_argv, env);
	if (!new_path)
		return ;
	if (!pwd_to_change)
		error_msg_return_void(MSG_ERR_PWD, "", 5, 1);
	update_old_pwd(env, pwd_to_change);
	update_pwd(env, new_path);
}

