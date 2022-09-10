/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:28:23 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/10 13:14:38 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_pwd(t_env *env)
{
	char *pwd;

	pwd = get_cur_dir(env);
	if(!pwd)
		trigger_pwd_error();
	write(0, pwd, ft_strlen(pwd));
	write(0, "\n", 1);
	free(pwd);
}
