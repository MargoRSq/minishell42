/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:22:05 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/28 21:53:11 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(t_env **env, char **cmd_argv)
{
	int	i;

	i = 1;
	while (cmd_argv[i])
	{
		if (!check_valid_env_key(cmd_argv[i]))
			return (error_msg_return_void(MSG_ERR_UNSET_KEY,
					cmd_argv[i], key_error, 0));
		envlst_delete_elem(cmd_argv[i], env);
		i++;
	}
}
