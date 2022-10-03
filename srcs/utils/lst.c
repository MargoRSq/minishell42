#include "minishell.h"

t_token	*tokenlst_new(char *start, int len, int code)
{
	t_token	*elem;

	elem = (t_token *)malloc(sizeof(t_token));
	if (!elem)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
	elem->start = start;
	elem->code = code;
	elem->len = len;
	// elem->next = NULL;
	return (elem);
}

void	tokenlst_delete_elem(void *content)
{
	t_token	*to_delete;

	to_delete = (t_token *)(content);
	// free(to_delete->code);
	// free(to_delete->len);
	free(to_delete->start);
	free(to_delete);
}

void	cmdlst_delete_elem(void *content)
{
	t_cmd	*to_delete;

	to_delete = (t_cmd *)(content);
	free(to_delete->argv);
	// free(to_delete->counter);
	// free(to_delete->fd_in);
	// free(to_delete->fd_out);
	free(to_delete->fns_in);
	free(to_delete->fns_out);
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

void clean_all(t_list **envlst, t_list *cmdlst, t_list *tokenlst)
{
	ft_lstclear(envlst, envlst_delete_elem);
	ft_lstclear(&cmdlst, cmdlst_delete_elem);
	ft_lstclear(&tokenlst, tokenlst_delete_elem);
}