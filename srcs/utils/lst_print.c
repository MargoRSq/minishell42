#include "minishell.h"

void	print_tokens(void *vtokens)
{
	t_token	*token;

	token = (t_token *)vtokens;
	printf("{text=%s, code=%d, len=%d} ",
		 ft_substr(token->start, 0, token->len),
		 token->code, token->len);
}

void	print_cmds(void *vcmds)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd;
	printf("{cmd=%s} ", cmd->argv[0]);
}

// void	prin