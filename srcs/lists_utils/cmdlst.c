#include "minishell.h"

// void	cmdlst_add_back(t_cmd **lst, t_cmd *new)
// {
// 	t_cmd	*lst_elem;

// 	if (!*lst)
// 	{
// 		(*lst) = new;
// 		return ;
// 	}
// 	lst_elem = cmdlst_last(*lst);
// 	lst_elem->next = new;
// }

// void	cmdlst_clear(t_cmd **lst)
// {
// 	t_cmd	*cur;
// 	t_cmd	*next;

// 	if (!lst || !(*lst))
// 		return ;
// 	cur = (*lst);
// 	next = cur;
// 	while (cur)
// 	{
// 		next = cur->next;
// 		// free(cur->value);
// 		// free(cur->key);
// 		free(cur);
// 		cur = next;
// 	}
// 	*lst = NULL;
// }
// t_cmd	*cmdlst_last(t_cmd *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }


static	t_file	*new_redir(t_list *tokenlst, t_token_type code)
{
	t_file	*file;
	t_token	*token;
	char	*name;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
	token = (t_token *)tokenlst->content;
	name = ft_substr(token->start, 0, (size_t)token->len);
	if (!name)
		return (NULL);
	file->name = name;
	file->type = code;
	return (file);
}

static void fill_params(t_list *tokenlst, t_cmd *cmd)
{
	int		k;
	t_token	*token;
	t_cmd	*curr_cmd;

	k = -1;
	token = (t_token *)tokenlst->content;
	curr_cmd = (t_cmd *)cmd;
	while (tokenlst && ((t_token *)(tokenlst->content))->code != lpipe)
	{
		token = (t_token *)tokenlst->content;
		if (token->code == r_in || token->code == r_out || token->code == r_append
			|| token->code == r_heredoc)
		{
			if (token->code == r_in || token->code == r_heredoc)
				ft_lstadd_back(&curr_cmd->fns_in, ft_lstnew(new_redir(tokenlst->next, token->code)));
			else if (token->code == r_out || token->code == r_append)
				ft_lstadd_back(&curr_cmd->fns_out, ft_lstnew(new_redir(tokenlst->next, token->code)));
			if (tokenlst->next && tokenlst->next->next)
			{
				token = (t_token *)(tokenlst->next->next->content);
				tokenlst = tokenlst->next->next;
			}
			else
				break;
		}
		else
		{
			curr_cmd->argv[++k] = ft_substr(token->start, 0, (size_t)token->len);
			if (!curr_cmd->argv[k])
				return ;
			tokenlst = tokenlst->next;
		}
	}
}

t_cmd	*cmdlst_new(t_list *tokens)
{
	t_cmd	*elem;
	t_count	counter;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	if (!elem)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
	counter = count_entities(tokens);
	// printf("in=%d out=%d words=%d\n", counter.in, counter.out, counter.words);
	elem->argv = (char **)malloc(sizeof(char *) * (counter.words + 1));
	elem->argv[counter.words] = NULL;
	elem->fns_in = NULL;
	elem->fns_out = NULL;
	fill_params(tokens, elem);
	// elem->next = NULL;
	elem->counter = counter;
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
// 		printf("{cmd=%s, args=%d, in=%d, out=%d} ",
// 			tmp->name, tmp->counter.words, tmp->counter.in, tmp->counter.out);
// 		tmp = tmp->next;
// 		if (tmp == NULL)
// 		{
// 			printf("\n");
// 			return ;
// 		}
// 	}
// }
