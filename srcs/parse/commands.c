/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:04 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/09/28 20:20:57 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_commands(t_list *tokens)
{
	// t_count	counter;
	t_list	*cmds;
	t_cmd	*cmd;
	// t_token *token;
	// t_list *next;

	cmds = NULL;
	cmd = cmdlst_new(tokens);
	ft_lstadd_back(&cmds, ft_lstnew(cmd));
	ft_lstiter(cmds, print_cmds);
	
	// while (token)
	// {
	// 	// next = ((t_list *)token)->next;
	// 	while (token && ((t_token *)token)->code != lpipe)
	// 		token = (t_token *)((t_list *)token)->next;
	// 	if (token)
	// 		token = (t_token *)((t_list *)token)->next;
	// 	else
	// 		break ;
	// }
	// cmdlst_print(cmds);
	return (cmds);
}
