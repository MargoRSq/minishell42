/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:23:57 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/13 15:59:33 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tmp	create_tmp_token(int len, int code, char *line)
{
	t_tmp	tkn;

	if (code == word)
		tkn = (t_tmp){.len = len, .type = 0, .str = line};
	else if (code == d_quote_str)
		tkn = (t_tmp){.len = len, .type = 1, .str = line + 1};
	else if (code == s_quote_str)
		tkn = (t_tmp){.len = len, .type = 2, .str = line + 1};
	else
		tkn = (t_tmp){.len = len, .tmp_code = code, .type = 3, .str = line};
	return (tkn);
}

t_token	*unpack_tmp_token(t_tmp tkn, t_list *envlst)
{
	int		final_len;
	char	*new_start;
	t_len	lns;

	if (tkn.type < 2)
	{
		final_len = count_final_len(tkn.str, tkn.len, tkn.type, envlst);
		lns = (t_len){.len = tkn.len, .final_len = final_len};
		new_start = unpack(tkn.str, lns, tkn.type, envlst);
		return (tokenlst_new(new_start, final_len, word));
	}
	else if (tkn.type == 2)
		return (tokenlst_new(tkn.str, tkn.len, s_quote_str));
	else
		return (tokenlst_new(tkn.str, tkn.len, tkn.tmp_code));
}
