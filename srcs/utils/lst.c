#include "minishell.h"

t_token	*tokenlst_new(char *start, int len, int code)
{
	t_token	*elem;

	elem = (t_token *)malloc(sizeof(t_token));
	if (!elem)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	elem->start = start;
	elem->code = code;
	elem->len = len;
	return (elem);
}

void	tokenlst_delete_elem(void *content)
{
	t_token	*to_delete;

	to_delete = (t_token *)(content);
	if (to_delete->code == word && ft_strlen(to_delete->start))
		free(to_delete->start);
	free(to_delete);
}

void	cmdlst_delete_elem(void *content)
{
	t_cmd	*to_delete;
	int		i;

	to_delete = (t_cmd *)(content);
	i = -1;
	while (to_delete->argv[++i])
		free(to_delete->argv[i]);
	free(to_delete->argv);
	if (to_delete->infile)
		free(to_delete->infile);
	if (to_delete->outfile)
		free(to_delete->outfile);
	free(to_delete);
}

void	envlst_delete_elem(void *content)
{
	t_env	*to_delete;

	to_delete = (t_env *)(content);
	free(to_delete->value);
	free(to_delete->key);
	free(to_delete);
}

static void	unlink_heredoc_tmp(t_list *tokenlst)
{
	t_list	*tok_tmp;
	t_token	*token;

	tok_tmp = tokenlst;
	while (tok_tmp)
	{
		token = (t_token *)tok_tmp->content;
		if (token->code == r_heredoc)
			unlink(((t_token *)((tok_tmp->next)->content))->start);
		tok_tmp = tok_tmp->next;
	}
}

void	clean_tokens_cmds(t_list *cmdlst, t_list *tokenlst)
{
	unlink_heredoc_tmp(tokenlst);
	ft_lstclear(&tokenlst, tokenlst_delete_elem);
	ft_lstclear(&cmdlst, cmdlst_delete_elem);
}
