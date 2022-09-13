/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:12:19 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/10 13:14:25 by angelinamaz      ###   ########.fr       */
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