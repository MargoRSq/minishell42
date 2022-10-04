/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:21 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/04 13:16:04 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_token(char *line, int len, t_env *env)
{
	t_tmp	tkn;
	int		code;
	char	*tmp;

	tmp = line;
	if (len == -1)
		return (NULL);
	code = get_code((int)*tmp, len);
	tkn = create_tmp_token(len, code, line);
	return (unpack_tmp_token(tkn, env));
}

t_list	*lex_line(char *line, t_env *env)
{
	int		i;
	int		len;
	t_list	*tokens;
	t_token	*token;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		if (line[i] == space)
			i++;
		else
		{
			len = find_end(&line[i]);
			token = create_token(&line[i], len, env);
			ft_lstadd_back(&tokens, ft_lstnew(token));
			i += get_skip_distance(&line[i], len);
		}
	}
	return (tokens);
}
