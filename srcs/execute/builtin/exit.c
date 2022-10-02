/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:07:23 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/02 17:45:39 by angelinamaz      ###   ########.fr       */
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

void	execute_exit(t_env *envlst, char **cmd_argv)
{
	int	i;
	int	len_arr;

	i = 0;
	len_arr = count_arg(cmd_argv);
	write(STDERR_FILENO, "exit\n", 6);
	if (len_arr == 1)
		return (error_msg_return_void("", NULL, 0, 1));
	else if (len_arr > 1)
	{
		while (ft_isdigit(cmd_argv[1][i]))
			i++;
		if ((size_t)i != ft_strlen(cmd_argv[1]))
			return (error_msg_return_void(MSG_ERR_EXIT_NUM,
					cmd_argv[1], 255, 1));
		else if (len_arr == 2)
			return (error_msg_return_void("", NULL,
					ft_atoi(cmd_argv[1]) % 256, 1));
		else if (len_arr > 1)
			return (error_msg_return_void(MSG_ERR_EXIT_ARGS, NULL, 1, 0));
	}
}
