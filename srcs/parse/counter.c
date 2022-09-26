/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:09 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/09/26 14:17:38 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int inline	count_redirs(t_token *tokens, int token_code)
{
	int		counter;
	t_token	*tmp;

	counter = 0;
	tmp = tokens;
	while (tmp && tmp->code != lpipe)
	{
		if (tmp->code == token_code)
		{
			counter++;
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break ;
		}
		else
			tmp = tmp->next;
	}
	return (counter);
}

static int inline	count_words(t_token *tokens)
{
	int		counter;
	t_token	*tmp;

	counter = 0;
	tmp = tokens;
	while (tmp && tmp->code != lpipe)
	{
		if (tmp->code == r_out || tmp->code == r_append || tmp->code == r_in
			|| tmp->code == r_heredoc)
		{
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break ;
		}
		else
		{
			counter++;
			tmp = tmp->next;
		}
	}
	return (counter);
}

t_count	count_entities(t_token *tokens)
{
	t_count	counter;

	counter.in = count_redirs(tokens, r_in);
	counter.in += count_redirs(tokens, r_heredoc);
	counter.out = count_redirs(tokens, r_out);
	counter.words = count_words(tokens);
	return (counter);
}
