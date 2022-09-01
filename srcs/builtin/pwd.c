/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:28:23 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/01 13:56:52 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_pwd(t_sh *sh)
{
	char *cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (cur_dir == NULL)
		cur_dir = get_env_value("PWD", sh->env);
	if (!cur_dir)
		printf("error");
	write(0, cur_dir, ft_strlen(cur_dir));
	write(0, "\n", 1);
	free(cur_dir);
}