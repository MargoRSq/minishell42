#include "minishell.h"

static int	check_access(t_token *word_token)
{
	int		result;
	char	*filename;

	filename = ft_substr(word_token->start, 0, word_token->len);
	result = access(filename, F_OK);
	free(filename);
	return (result);
}

void	check_tokens(t_list *tokenlst, t_env *env)
{
	t_token	*token;

	// next = (t_token *)(token->next);
	token = (t_token *)(tokenlst->content);
	if (token->code == lpipe || ((t_token *)ft_lstlast(tokenlst))->code == lpipe)
		return error_msg_return_void(MSG_ERR_PIPE_LOC, NULL, 127, 1);
	while (tokenlst)
	{
		token = (t_token *)(tokenlst->content);
		if (token->code == r_in || token->code == r_out
			|| token->code == r_append || token->code == r_heredoc)
		{
			if (!tokenlst->next)
				return error_msg_return_void(MSG_ERR_REDIR_PARSE, NULL, 127, 1);
			else if (((t_token *)tokenlst->next->content)->code != word)
				return error_msg_return_void(MSG_ERR_REDIR_PARSE, NULL, 127, 1);
			else if (token->code == r_heredoc)
				heredoc(tokenlst->next->content, env);
			// else if (check_access(tokenlst->next->content) == -1)
			// 	return error_msg_return_void(MSG_ERR_FILE_NEXISTS, NULL, 127,
			// 								 1);
		}
		tokenlst = tokenlst->next;
	}
}
