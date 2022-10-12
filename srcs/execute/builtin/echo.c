/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:49 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/12 18:47:20 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(char **cmd_argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!cmd_argv[1])
	{
		printf("\n");
		return ;
	}
	while (cmd_argv[i] && !ft_strcmp(cmd_argv[i], "-n"))
	{
		flag = 1;
		i++;
	}
	while (cmd_argv[i])
	{
		printf("%s", cmd_argv[i]);
		if (cmd_argv[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
}
