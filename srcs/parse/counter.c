/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:09 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/09/29 13:46:16 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int inline	count_redirs(t_list *tokenlst, t_token_type token_code)
{
	int		counter;
	t_token	*token;

	counter = 0;
	token = (t_token *)(tokenlst->content);
	while (tokenlst && ((t_token *)(tokenlst->content))->code != lpipe)
	{
		token = (t_token *)(tokenlst->content);
		if (token->code == token_code)
		{
			counter++;
			if (tokenlst->next && tokenlst->next->next)
				token = (t_token *)(tokenlst->next->next->content);
			else
				break ;
		}
		else
			tokenlst = tokenlst->next;
	}
	return (counter);
}

static int inline	count_words(t_list *tokenlst)
{
	int		counter;
	t_token	*token;

	counter = 0;
	token = (t_token *)(tokenlst->content);
	while (tokenlst && ((t_token *)(tokenlst->content))->code != lpipe)
	{
		token = (t_token *)(tokenlst->content);
		if (token->code == r_out || token->code == r_append || token->code == r_in
			|| token->code == r_heredoc)
		{
			if (tokenlst->next && tokenlst->next->next)
				token = (t_token *)(tokenlst->next->next)->content;
			else
				break ;
		}
		else
		{
			counter++;
			if (tokenlst->next)
				token = (t_token *)(tokenlst->next)->content;
			tokenlst = tokenlst->next;
		}
	}
	return (counter);
}

t_count	count_entities(t_list *tokens)
{
	t_count	counter;

	counter.in = count_redirs(tokens, r_in);
	counter.in += count_redirs(tokens, r_heredoc);
	counter.out = count_redirs(tokens, r_out);
	counter.words = count_words(tokens);
	return (counter);
}
