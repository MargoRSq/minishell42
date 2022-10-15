/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:49:02 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/15 13:05:02 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_file	*create_file(t_token_type code, t_token *last)
{
	t_file			*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	file->name = last->start;
	file->type = code;
	return (file);
}

static void	find_file(short type, t_list *tokenlst,
	t_token_type *code, t_token **last)
{
	t_token	*token;

	token = (tokenlst->content);
	if (((token->code == r_in || token->code == r_heredoc) && type == 1)
		|| ((token->code == r_out || token->code == r_append) && type == 0))
	{
		*last = (t_token *)(tokenlst->next->content);
		*code = ((t_token *)(tokenlst->content))->code;
	}
}

static t_file	*fetch_last_file(t_list	*tokenlst, short type)
{
	t_token			*last;
	t_file			*file;
	t_token_type	code;

	last = NULL;
	file = NULL;
	while (tokenlst)
	{
		find_file(type, tokenlst, &code, &last);
		tokenlst = tokenlst->next;
	}
	if (last)
		file = create_file(code, last);
	return (file);
}

static void	fill_params(t_list *tokenlst, t_cmd *cmd)
{
	int		k;
	t_token	*token;

	k = -1;
	while (tokenlst && ((t_token *)(tokenlst->content))->code != lpipe)
	{
		token = (t_token *)tokenlst->content;
		if (token->code == r_in || token->code == r_out || \
			token->code == r_append || token->code == r_heredoc)
		{
			if (tokenlst->next && tokenlst->next->next)
				tokenlst = tokenlst->next->next;
			else
				break ;
		}
		else
		{
			cmd->argv[++k] = ft_substr(token->start, 0, (size_t)token->len);
			if (!cmd->argv[k])
				return ;
			tokenlst = tokenlst->next;
		}
	}
}

t_cmd	*cmdlst_new(t_list *tokenlst)
{
	t_cmd	*elem;
	t_count	counter;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	if (!elem)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	counter = count_entities(tokenlst);
	elem->argv = (char **)malloc(sizeof(char *) * (counter.words + 1));
	elem->argv[counter.words] = NULL;
	elem->infile = fetch_last_file(tokenlst, 1);
	elem->outfile = fetch_last_file(tokenlst, 0);
	fill_params(tokenlst, elem);
	elem->counter = counter;
	return (elem);
}
