/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:40:31 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/12 18:40:32 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multi_pipe_process(t_list **envlst, t_list *cmdlst, t_fd *fds)
{
	t_cmd		*tmp;
	t_cmd		*prev;
	int			i;

	prev = NULL;
	i = 0;
	while (cmdlst && ++i)
	{
		tmp = (t_cmd *)(cmdlst->content);
		if (prev == NULL)
			exec_first_cmd(*envlst, tmp, fds);
		else if (cmdlst->next == NULL)
			exec_last_cmd(*envlst, tmp, fds, i);
		else
			exec_middle_cmd(*envlst, tmp, fds, i);
		prev = tmp;
		cmdlst = cmdlst->next;
	}
	while (wait(0) != -1)
		;
}
