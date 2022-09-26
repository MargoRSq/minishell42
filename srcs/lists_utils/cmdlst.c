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

static void fill_params(t_token *tokens, t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	int		is_cmd;
	t_token	*tmp;
	t_token	*arg;

	i = -1;
	j = -1;
	k = -1;
	is_cmd = 0;
	tmp = tokens;
	while (tmp && tmp->code != lpipe)
	{
		arg = tmp->next;
		if (tmp->code == r_in || tmp->code == r_out || tmp->code == r_append
			|| tmp->code == r_heredoc)
		{
			if (tmp->code == r_in || tmp->code == r_heredoc)
				cmd->fns_in[++i] = (t_file){ .name=ft_substr(arg->start, 0, (size_t)arg->len),
											.type=r_in};
			else if (tmp->code == r_out)
				cmd->fns_out[++j] = (t_file){ .name=ft_substr(arg->start, 0, (size_t)arg->len),
											.type=r_out};
			else if (tmp->code == r_append)
				cmd->fns_out[++j] = (t_file){ .name=ft_substr(arg->start, 0, (size_t)arg->len),
											.type=r_append};
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break;
		}
		else
		{
			if (!is_cmd)
			{
				is_cmd = 1;
				cmd->name = ft_substr(tmp->start, 0, (size_t)tmp->len);
				cmd->argv[++k] = ft_substr(tmp->start, 0, (size_t)tmp->len);
			}
			else
				cmd->argv[++k] = ft_substr(tmp->start, 0, (size_t)tmp->len);
		tmp = tmp->next;
		}
	}
}

t_cmd	*cmdlst_new(t_token *tokens)
{
	t_cmd	*elem;
	t_count	counter;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	if (!elem)
		return trigger_malloc_error();
	counter = count_entities(tokens);
	// printf("in=%d out=%d words=%d\n", counter.in, counter.out, counter.words);
	elem->argv = (char **)malloc(sizeof(char *) * (counter.words + 1));
	elem->argv[counter.words] = NULL;
	elem->fns_in = (t_file *)malloc(sizeof(t_file) * (counter.in + 1));
	elem->fns_out = (t_file *)malloc(sizeof(t_file) * (counter.out + 1));
	fill_params(tokens, elem);
	elem->next = NULL;
	elem->counter = counter;
	return (elem);
}

void	cmdlst_print(t_cmd *lst)
{
	t_cmd	*tmp;

	tmp = lst;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		printf("{cmd=%s, args=%d, in=%d, out=%d} ",
			tmp->name, tmp->counter.words, tmp->counter.in, tmp->counter.out);
		tmp = tmp->next;
		if (tmp == NULL)
		{
			printf("\n");
			return ;
		}
	}
}
