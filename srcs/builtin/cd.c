/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:57 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/10 14:07:20 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_pwd_values(t_env *env, char *old_path, char *new_path)
{
	t_env *updated_old_pwd;
	t_env *updated_pwd;

	updated_old_pwd = envlst_new("OLD_PWD", ft_strdup(old_path));
	updated_pwd =  envlst_new("PWD", ft_strdup(new_path));
	if(!updated_old_pwd)
		exit ;
	if(!updated_pwd)
		exit ;
	envlst_delete_elem("OLD_PWD", &env);
	envlst_delete_elem("PWD", &env);
	envlst_add_back(&env, updated_old_pwd);
	envlst_add_back(&env, updated_pwd);
}

static char *go_home(t_env *env)
{
	char *new_path;
	
	new_path = get_env_value("HOME", env);
	if(!new_path)
	{
		trigger_home_error();
		return (1);
	}
	if(chdir(new_path) == -1)
		trigger_home_error();
	return(new_path);
}

static char	*handle_cd_argv(char **cmd_argv)
{
	char *new_path;

	new_path = ft_strdup(cmd_argv[1]);
	if(chdir(new_path) == -1)
		// error not existing path
	return(new_path);
}

void execute_cd(t_env *env, char **cmd_argv)
{
	char *old_path;
	char *new_path;

	if(!cmd_argv[1] || cmd_argv[1] == '~')
		new_path = go_home(env);
	else
		new_path = go_cd_argv(cmd_argv);
	old_path = get_cur_dir(env);
	if(!old_path)
	{
		trigger_pwd_error();
		return (1);		
	}
	update_pwd_values(env, old_path, new_path);
}