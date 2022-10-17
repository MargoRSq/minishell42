/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:49 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/17 15:18:55 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_arg(char **cmd_argv, int i)
{
	while (cmd_argv[i])
	{
		printf("%s", cmd_argv[i]);
		if (cmd_argv[i + 1])
			printf(" ");
		i++;
	}
}

void	execute_echo(char **cmd_argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!cmd_argv[1])
	{
		printf("\n");
		g_status.exit_code = 0;
		return ;
	}
	while (cmd_argv[i] && !ft_strcmp(cmd_argv[i], "-n"))
	{
		flag = 1;
		i++;
	}
	print_arg(cmd_argv, i);
	if (flag == 0)
		printf("\n");
	g_status.exit_code = 0;
}
