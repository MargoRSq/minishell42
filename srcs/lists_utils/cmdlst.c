#include "minishell.h"

void	cmdlst_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*lst_elem;

	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	lst_elem = cmdlst_last(*lst);
	lst_elem->next = new;
}

void	cmdlst_clear(t_cmd **lst)
{
	t_cmd	*cur;
	t_cmd	*next;

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
t_cmd	*cmdlst_last(t_cmd *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*cmdlst_new(char *start, int len, int code)
{
	t_cmd	*elem;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	if (!elem)
		return trigger_malloc_error();
	// elem->start = start;
	// elem->len = len;
	// elem->code = code;
	elem->next = NULL;
	return (elem);
}

// void	cmdlst_print(t_cmd *lst)
// {
// 	t_cmd	*tmp;

// 	tmp = lst;
// 	if (!tmp)
// 		return ;
// 	while (tmp != NULL)
// 	{
// 		printf("{code=%d, len=%d} ", tmp->code, tmp->len);
// 		tmp = tmp->next;
// 		if (tmp == NULL)
// 		{
// 			printf("\n");
// 			return ;
// 		}
// 	}
// }
