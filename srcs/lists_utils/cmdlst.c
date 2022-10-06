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

	k = -1;
	while (tokenlst && ((t_token *)(tokenlst->content))->code != lpipe)
	{
		token = (t_token *)tokenlst->content;
		if (token->code == r_in || token->code == r_out || token->code == r_append
			|| token->code == r_heredoc)
		{
			if (tokenlst->next && tokenlst->next->next)
				tokenlst = tokenlst->next->next;
			else
				break;
		}
		else
		{
			cmd->argv[++k] = ft_substr(token->start, 0, (size_t)token->len);
			if (!cmd->argv[k])
				return ;
			tokenlst = tokenlst->next;
		}
	}
}

static t_file	*fetch_last_file(t_list	*tokenlst, short type)
{
	t_token	*last;
	t_file	*file;
	t_token_type	code;
	
	last = NULL;
	file = NULL;
	if (type == 1)
	{
		while (tokenlst)
		{
			if (((t_token *)(tokenlst->content))->code == r_in
				|| ((t_token *)(tokenlst->content))->code == r_append)
				{
					last = (t_token *)(tokenlst->next->content);
					code = ((t_token *)(tokenlst->content))->code;
				}
			tokenlst = tokenlst->next;
		}
	}
	else
	{
		while (tokenlst)
		{
			if (((t_token *)(tokenlst->content))->code == r_out)
				{
					last = (t_token *)(tokenlst->next->content);
					code = ((t_token *)(tokenlst->content))->code;
				}
			tokenlst = tokenlst->next;
		}
	}
	if (last)
	{
		file = (t_file *)malloc(sizeof(t_file));
		if (!file)
			return (error_msg_return_null(MSG_ERR_MEM, NULL, malloc_error, 1));
		file->name = last->start;
		file->type = code;
	}
	return (file);
}

t_cmd	*cmdlst_new(t_list *tokenlst)
{
	t_cmd	*elem;
	t_count	counter;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	if (!elem)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
	counter = count_entities(tokens);
	elem->argv = (char **)malloc(sizeof(char *) * (counter.words + 1));
	elem->argv[counter.words] = NULL;
	elem->infile = fetch_last_file(tokenlst, 1);
	elem->outfile = fetch_last_file(tokenlst, 0);
	fill_params(tokenlst, elem);
	elem->counter = counter;
	return (elem);
}
