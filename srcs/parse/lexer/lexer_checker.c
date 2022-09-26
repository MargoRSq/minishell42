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

void	check_tokens(t_token *token, t_env *env)
{
	if (token->code == lpipe || tokenlst_last(token)->code == lpipe)
		return error_msg_return_void(MSG_ERR_PIPE_LOC, NULL, 127, 1);
	while (token)
	{
		if (token->code == r_in || token->code == r_out
			|| token->code == r_append || token->code == r_heredoc)
		{
			if (!(token->next))
				return error_msg_return_void(MSG_ERR_REDIR_PARSE, NULL, 127, 1);
			else if (token->next->code != word)
				return error_msg_return_void(MSG_ERR_REDIR_PARSE, NULL, 127, 1);
			else if (token->code == r_heredoc)
				heredoc(token->next, env);
			else if (check_access(token->next) == -1)
				return error_msg_return_void(MSG_ERR_FILE_NEXISTS, NULL, 127,
											 1);
		}
		token = token->next;
	}
}
