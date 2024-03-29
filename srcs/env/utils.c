/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:33:12 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 18:33:13 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *key, t_list *envlst)
{
	t_env	*tmp;

	while (envlst)
	{
		tmp = (t_env *)(envlst->content);
		if (!ft_strcmp(key, tmp->key))
			return (tmp->value);
		envlst = envlst->next;
	}
	return (NULL);
}
