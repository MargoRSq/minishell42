/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:22:05 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/02 12:36:18 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(t_list **envlst, char **cmd_argv)
{
	int	i;

	i = 1;
	while (cmd_argv[i])
	{
		if (!check_valid_env_key(cmd_argv[i]))
			return (error_msg_return_void(MSG_ERR_UNSET_KEY,
					cmd_argv[i], key_error, 0));
		envlst_delete_one(cmd_argv[i], envlst);
		i++;
	}
}
