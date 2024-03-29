/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:00:28 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/12 15:58:23 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access(t_token *filename_token, t_token_type code)
{
	int		result;
	char	*filename;

	result = 1;
	filename = ft_substr(filename_token->start, 0, filename_token->len);
	if (!filename)
		return (-1);
	if (code == r_in)
		result = access(filename, F_OK | R_OK);
	free(filename);
	return (result);
}

void	check_tokens(t_list *tokenlst)
{
	t_token	*token;

	if (((t_token *)(tokenlst->content))->code == lpipe
		|| ((t_token *)ft_lstlast(tokenlst))->code == lpipe)
		return (error_msg_return_void(MSG_ERR_PIPE_LOC, NULL, 127, 1));
	while (tokenlst)
	{
		token = (t_token *)(tokenlst->content);
		if (token->code == r_in || token->code == r_out
			|| token->code == r_append || token->code == r_heredoc)
		{
			if (!tokenlst->next)
				return (error_msg_return_void(MSG_ERR_REDIR_PARSE, NULL,
						127, 1));
			else if (((t_token *)tokenlst->next->content)->code != word)
				return (error_msg_return_void(MSG_ERR_REDIR_PARSE, NULL,
						127, 1));
			else if (token->code == r_heredoc)
				heredoc(tokenlst->next->content);
			else if (check_access(tokenlst->next->content, token->code) == -1)
				return (error_msg_return_void(MSG_ERR_FILE_NEXISTS, NULL, 127,
						0));
		}
		tokenlst = tokenlst->next;
	}
}
