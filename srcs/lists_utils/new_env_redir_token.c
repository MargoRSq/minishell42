/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env_redir_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:57:57 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 17:02:58 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static	t_file	*new_redir(t_list *tokenlst, t_token_type code)
{
	t_file	*file;
	t_token	*token;
	char	*name;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	token = (t_token *)tokenlst->content;
	name = ft_substr(token->start, 0, (size_t)token->len);
	if (!name)
		return (NULL);
	file->name = name;
	file->type = code;
	return (file);
}

t_token	*tokenlst_new(char *start, int len, int code)
{
	t_token	*elem;

	elem = (t_token *)malloc(sizeof(t_token));
	if (!elem)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	elem->start = start;
	elem->code = code;
	elem->len = len;
	return (elem);
}
