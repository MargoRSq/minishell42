#include "minishell.h"

void	tokenlst_add_back(t_token **lst, t_token *new)
{
	t_token	*lst_elem;

	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	lst_elem = tokenlst_last(*lst);
	lst_elem->next = new;
}

void	tokenlst_clear(t_token **lst)
{
	t_token	*cur;
	t_token	*next;

	if (!lst || !(*lst))
		return ;
	cur = (*lst);
	next = cur;
	while (cur)
	{
		next = cur->next;
		// free(cur->value);
		// free(cur->key);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}
t_token	*tokenlst_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*tokenlst_new(char *start, int len, int code)
{
	t_token	*elem;

	elem = (t_token *)malloc(sizeof(t_token));
	if (!elem)
		return (NULL);
	elem->start = start;
	elem->len = len;
	elem->code = code;
	elem->next = NULL;
	return (elem);
}

void	tokenlst_print(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		printf("{code=%d, len=%d} ", tmp->code, tmp->len);
		tmp = tmp->next;
		if (tmp == NULL)
		{
			printf("\n");
			return ;
		}
	}
}
