/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:07:23 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/09/25 21:00:04 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	return (i);
}

void	execute_exit(t_env *env, char **cmd_argv)
{
	int	i;
	int	len_arr;

	i = 0;
	len_arr = count_arg(cmd_argv);
	write(STDERR_FILENO, "exit\n", 6);
	if (len_arr == 0)
		return(error_msg_return_void("", "", 0, 1));
	else if (len_arr > 0)
	{
		while (ft_isdigit(cmd_argv[0][i]))
			i++;
		if ((size_t)i != ft_strlen(cmd_argv[0]))
			return(error_msg_return_void(MSG_ERR_EXIT_NUM, cmd_argv[0], 255, 1));
		else if (len_arr == 1)
			return(error_msg_return_void("", "", ft_atoi(cmd_argv[0]) % 256, 1));
		else if (len_arr > 0)
			return(error_msg_return_void(MSG_ERR_EXIT_ARGS, "", 1, 0));
	}
}

