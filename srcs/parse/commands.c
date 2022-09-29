/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:04 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/09/29 14:09:38 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_commands(t_list *tokenlst)
{
	t_list	*cmds;

	cmds = NULL;
	while (tokenlst)
	{
		ft_lstadd_back(&cmds, ft_lstnew(cmdlst_new(tokenlst)));
		while (tokenlst && ((t_token *)tokenlst->content)->code != lpipe)
			tokenlst = tokenlst->next;
		if (tokenlst)
			tokenlst = tokenlst->next;
		else
			break ;
	}
	return (cmds);
}
