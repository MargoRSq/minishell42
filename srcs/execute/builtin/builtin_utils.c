/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:12:19 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/29 17:48:26 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cur_dir(t_env *env)
{
	char	*cwd;

	cwd = get_env_value("PWD", env);
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

void	append_env_var(t_list *envlst, char *new_key, char *new_value)
{
	t_list	*new_elem;

	if (!new_value)
		new_value = ft_strdup("");
	new_elem = ft_lstnew(envlst_new(new_key, new_value));
	if (!new_elem)
		return (error_msg_return_void(MSG_ERR_MEM, "", malloc_error, 1));
	ft_lstadd_back(&envlst, new_elem);
}
