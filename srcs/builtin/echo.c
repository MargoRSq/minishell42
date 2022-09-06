/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:49 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/01 16:27:04 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_echo(t_cmd *cmd)
{
	int i;
	
	if (!cmd->args[1])
	{
		printf("\n");
		return ;
	}
	while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n",
			ft_strlen(cmd->args[i])))
		i++;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(cmd->args[1], "-n", ft_strlen(cmd->args[1])))
	printf("\n");
}