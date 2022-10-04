/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:12:19 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/03 21:49:06 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cur_dir(t_list *envlst)
{
	char	*cwd;

	cwd = get_env_value("PWD", envlst);
	if (!cwd)
		cwd = getcwd(NULL, 0);
	return (cwd);
}

int	check_valid_env_key(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	while (*str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	check_valid_env_value(char *str)
{
	while (*str != '\0')
	{
		if (!ft_isascii(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	append_env_var(t_list *envlst, char *new_key, char *new_value)
{
	t_list	*new_elem;

	if (!new_value)
		new_value = ft_strdup("");
	new_elem = ft_lstnew(envlst_new(new_key, new_value));
	if(new_key)
		free(new_key);
	if(new_value)
		free(new_value);
	if (!new_elem)
		return (error_msg_return_void(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	ft_lstadd_back(&envlst, new_elem);
}

void	change_or_append(t_list *envlst, char *new_key, char *new_value)
{
	t_env	*tmp;
	t_list	*tmp_lst;

	tmp_lst = envlst;
	while (tmp_lst)
	{
		tmp = (t_env *)(tmp_lst->content);
		if (!ft_strcmp(new_key, tmp->key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			if (!tmp->value)
				return (error_msg_return_void(MSG_SYSCALL_ERR_MEM, NULL,
						malloc_error, 1));
			free(new_key);
			free(new_value);
			return ;
		}
		tmp_lst = tmp_lst->next;
	}
	append_env_var(envlst, new_key, new_value);
}
