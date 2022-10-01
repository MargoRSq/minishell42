/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:55 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/29 21:32:50 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_env(t_list *envlst, char **cmd_argv)
{
	if (cmd_argv[1])
		return (error_msg_return_void(MSG_ERR_ENV_ARGS, cmd_argv[1], 127, 0));
	if (envlst == NULL)
		error_msg_return_void(MSG_ERR_ENV, "", 2, 1);
	ft_lstiter(envlst, print_env);
	// envlst_print(envlst);
}
