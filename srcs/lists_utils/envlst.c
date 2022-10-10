/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:50:41 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 16:28:02 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_one(t_list *tmp_lst, char *key)
{
	t_env	*tmp;
	t_list	*to_delete;

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
	delete_one(tmp_lst, key);
}

static char	*make_str(t_env *tmp)
{
	char	*line;
	char	*help;

	if (tmp->value)
	{
		help = ft_strjoin (tmp->key, "=");
		line = ft_strjoin(help, tmp->value);
		free(help);
	}
	else
		line = ft_strdup(tmp->key);
	return (line);
}

char	**envlst_to_arr(t_list *envlst)
{
	char	**arr;
	t_env	*tmp;
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
		arr[i] = make_str(tmp);
		i++;
		envlst = envlst->next;
	}
	return (arr);
}
