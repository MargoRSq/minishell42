/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:40:28 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 18:42:02 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	find_equals_sign(char *str)
{
	int	j;

	j = -1;
	while (str[++j])
		if (str[j] == '=')
			return (j);
	return (-1);
}

t_list	*parse_envp(char **envp)
{
	t_list	*envlst;
	int		i;
	int		eq;
	char	*key;
	char	*value;

	envlst = NULL;
	i = -1;
	eq = 0;
	if (envp)
	{
		while (envp[++i])
		{
			eq = find_equals_sign(envp[i]);
			key = ft_substr(envp[i], 0, eq);
			value = ft_substr(envp[i], eq + 1, ft_strlen(envp[i]));
			if (!key || !value || eq == -1)
				return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
						malloc_error, 1));
			ft_lstadd_back(&envlst, ft_lstnew(envlst_new(key, value)));
		}
	}
	return (envlst);
}
