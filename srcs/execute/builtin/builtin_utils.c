/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:12:19 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/19 16:22:18 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_cur_dir(t_env *env)
{
	char *cwd;
	
	cwd = get_env_value("PWD", env);
	if(!cwd)
		cwd = getcwd(NULL, 0);
	return(cwd);
}

int check_valid_env_key(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int check_valid_env_value(char *str)
{
	while (*str != '\0')
	{
		if(!ft_isascii(*str))
			return(0);
		str++;
	}
	return (1);
}