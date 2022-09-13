/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:49 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/06 12:55:39 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_echo(char **cmd_argv)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	if (!cmd_argv[0])
	{
		printf("\n");
		return ;
	}
	if(!ft_strcmp(cmd_argv[0], "-n") && !cmd_argv[1])
	{
		printf("\n");
		return ;
	}
	if (!ft_strcmp(cmd_argv[0], "-n") && cmd_argv[1])
			flag = 1;
	while (cmd_argv[i])
	{
		{
			printf("%s", cmd_argv[i]);
			if (cmd_argv[i + 1])
				printf(" ");
			i++;
		}	
	}
	if (flag == 0)
		printf("\n");
}
