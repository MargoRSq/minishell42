/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:48:55 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/26 15:10:41 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_env(t_env *env,  char **cmd_argv)
{
	if(cmd_argv[0])
		return(error_msg_return_void(MSG_ERR_ENV_ARGS, cmd_argv[0], 127, 0));
	if(env == NULL)
		error_msg_return_void(MSG_ERR_ENV, "", 2, 1);
	envlst_print(env);
}
