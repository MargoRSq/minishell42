#include "minishell.h"

t_env	*envlst_new(char *key, char *value)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (!elem)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	elem->key = key;
	elem->value = value;
	return (elem);
}

void	envlst_delete_one(char *key, t_list **envlst)
{
	t_env	*tmp;
	t_list	*head;
	t_list	*tmp_lst;
	t_list	*to_delete;

	if (!envlst)
		return ;
	tmp = (t_env *)((*envlst)->content);
	if (!strcmp(key, tmp->key))
	{
		to_delete = (*envlst);
		head = (*envlst)->next;
		ft_lstdelone(to_delete, envlst_delete_elem);
		(*envlst) = head;
		return ;
	}
	tmp_lst = (*envlst);
	while (tmp_lst->next)
	{
		tmp = (t_env *)(tmp_lst->next->content);
		if (!strcmp(key, tmp->key))
		{
			to_delete = tmp_lst->next;
			tmp_lst->next = tmp_lst->next->next;
			ft_lstdelone(to_delete, envlst_delete_elem);
			return ;
		}
		tmp_lst = tmp_lst->next;
	}
}

char	**envlst_to_arr(t_list *envlst)
{
	char	**arr;
	t_env	*tmp;
	char	*help;
	int		i;
	int		len;

	if (!envlst)
		return (NULL);
	i = 0;
	len = ft_lstsize(envlst);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = NULL;
	while (i < len)
	{
		tmp = (t_env *)(envlst->content);
		help = ft_strjoin (tmp->key, "=");
		arr[i] = ft_strjoin(help, tmp->value);
		i++;
		envlst = envlst->next;
		free(help);
	}
	return (arr);
}
