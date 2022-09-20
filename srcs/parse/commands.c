/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:04 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/09/20 14:35:05 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_commands(t_token *tokens)
{
	t_count	counter;
	t_cmd	*cmds;

	cmds = NULL;
	while (tokens)
	{
		cmdlst_add_back(&cmds, cmdlst_new(tokens));
		while (tokens && tokens->code != lpipe)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
		else
			break ;
	}
	// cmdlst_print(cmds);
	return (cmds);
}
