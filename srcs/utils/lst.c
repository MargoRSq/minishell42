#include "minishell.h"

t_token	*tokenlst_new(char *start, int len, int code)
{
	t_token	*elem;

	elem = (t_token *)malloc(sizeof(t_token));
	if (!elem)
		return (error_msg_return_null(MSG_ERR_MEM, "", malloc_error, 1));
	elem->start = start;
	elem->code = code;
	elem->len = len;
	// elem->next = NULL;
	return (elem);
}