/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:55 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/17 14:59:17 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(t_list *envlst, char **cmd_argv)
{
	if (cmd_argv[1])
		return (error_msg_return_void(MSG_ERR_ENV_ARGS, cmd_argv[1],
				env_arg_error, 0));
	if (envlst == NULL)
		error_msg_return_void(MSG_ERR_ENV, NULL, env_error, 1);
	ft_lstiter(envlst, print_env);
	g_status.exit_code = 0;
}
