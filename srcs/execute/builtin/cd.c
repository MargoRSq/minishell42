/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:50:57 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/15 21:07:58 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_pwd_values(t_env *env, char *old_path, const char *new_path)
{
	t_env *updated_old_pwd;
	t_env *updated_pwd;

	updated_old_pwd = envlst_new("OLDPWD", ft_strdup(old_path));
	updated_pwd =  envlst_new("PWD", ft_strdup(new_path));
	if(!updated_old_pwd)
		return ; 
	if(!updated_pwd)
		return ; 
	envlst_delete_elem("OLDPWD", &env);
	envlst_add_back(&env, updated_old_pwd);
	envlst_delete_elem("PWD", &env);
	envlst_add_back(&env, updated_pwd);
}



static char *go_home(t_env *env)
{
	char *new_path;
	
	printf("home\n");
	new_path = get_env_value("HOME", env);
	if(!new_path)
		return (trigger_home_error());
	// printf("getcwd %s\n", getcwd(NULL, 0));
	if(chdir(new_path) == -1)
		trigger_home_error();
	// printf("getcwd %s\n", getcwd(NULL, 0));
	return(new_path);
}

static const char	*go_cd_argv(char **cmd_argv)
{
	const char *new_path;

	new_path = ft_strdup(cmd_argv[0]);
	if(chdir(new_path) == -1)
		return NULL; // error not existing path
	return(new_path);
}

static const char	*go_oldpwd(t_env *env)
{
	char *old_pwd;
	
	// printf("getcwd %s\n", getcwd(NULL, 0));
	old_pwd = get_env_value("OLDPWD", env);
	// printf("old_pwd %s\n", old_pwd);
	if(!old_pwd)
			return NULL;	
	else
	{
		if(chdir(old_pwd) == -1)
			return NULL; 
	}
	// printf("getcwd %s\n", getcwd(NULL, 0));
	return (old_pwd);
}

void execute_cd(t_env *env, char **cmd_argv)
{
	char *pwd_to_change;
	const char *new_path;
	char *old_pwd;
	
	old_pwd = get_env_value("OLDPWD", env);
	// printf("1 old_pwd %s\n", old_pwd);	
	pwd_to_change = get_cur_dir(env);
	// printf("1 pwd_to_change %s\n", pwd_to_change);
	
	if(!cmd_argv[0] || !ft_strcmp(cmd_argv[0], "~"))
		new_path = go_home(env);
	else if (!ft_strcmp(cmd_argv[0], "-"))
		new_path = go_oldpwd(env);
	else if (cmd_argv[0])
		new_path = go_cd_argv(cmd_argv);
	
	if(!pwd_to_change)
			printf(MSG_ERR_PWD);
	//not working
	// printf("1 new_path %s\n", new_path);
	update_pwd_values(env, pwd_to_change, new_path);
}