#include "minishell.h"

void	envlst_add_back(t_env **lst, t_env *new)
{
	t_env	*lst_elem;

	if (!new)
		return ;
	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	lst_elem = envlst_last(*lst);
	lst_elem->next = new;
}

void	envlst_clear(t_env **lst)
{
	t_env	*cur;
	t_env	*next;

	if (!lst || !(*lst))
		return ;
	cur = (*lst);
	next = cur;
	while (cur)
	{
		next = cur->next;
		free(cur->value);
		free(cur->key);
		free(cur);
		cur = next;
	}
	*lst = NULL;
}

t_env	*envlst_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_env	*envlst_new(char *key, char *value)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (!elem)
		return (error_msg_return_null(MSG_ERR_MEM, "", malloc_error, 1));
	elem->key = key;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

void	envlst_print(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		if(ft_strcmp(tmp->value, ""))
		{
			printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
			if (tmp == NULL)
				return ;
		}
	}
}


// void envlst_delete_elem(char *key, t_env **lst)
// {
// 	t_env *tmp;
// 	t_env *to_delete;

// 	if (!lst || !(*lst))
// 		return ;
// 	tmp = (*lst);
// 	if(!strcmp(key, tmp->key))
// 	{
// 		to_delete = tmp;
// 		tmp = tmp->next;
// 		free(to_delete->value);
// 		free(to_delete->key);
// 		free(to_delete);
// 		return ;
// 	}
// 	while(tmp->next)
// 	{
// 		if(!strcmp(key, tmp->next->key))
// 		{
// 			to_delete = tmp->next;
// 			tmp->next = tmp->next->next;
// 			free(to_delete->value);
// 			free(to_delete->key);
// 			free(to_delete);
// 			return ;
// 		}
// 		tmp = tmp->next;
// 	}
// }



void envlst_delete_elem(char *key, t_env **lst)
{
	t_env *tmp;
	t_env *head;
	t_env *to_delete;


	if (!lst)
		return ;
	if(!strcmp(key, (*lst)->key))
	{
		to_delete = (*lst);
		head = (*lst)->next;
		// *lst = (*lst)->next;
		free(to_delete->value);
		free(to_delete->key);
		free(to_delete);
		(*lst) = head;
		return ;
	}
	tmp = (*lst);
	while(tmp->next)
	{
		if(!strcmp(key, tmp->next->key))
		{
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			free(to_delete->value);
			free(to_delete->key);
			free(to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}

int	envlst_size(t_env *lst)
{
	int	count;

	count = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

char **envlst_to_arr(t_env *lst)
{
	char **arr;
	t_env *tmp;
	char *help;
	int i;
	int len;

	if (!lst)
		return (NULL);
	tmp = lst;
	i = 0;
	len = envlst_size(lst);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if(!arr)
		return (NULL);
	arr[len] = NULL;
	while(i < len)
	{
		help = ft_strjoin(tmp->key, "=");
		arr[i] = ft_strjoin(help, tmp->value);
		i++;
		tmp = tmp->next;
		free(help);
	}
	return (arr);
}