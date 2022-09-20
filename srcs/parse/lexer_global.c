/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:17 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/09/20 14:35:18 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline int	get_code(int sy, int len)
{
	if (sy == s_quote)
		return (s_quote_str);
	else if (sy == d_quote)
		return (d_quote_str);
	else if (sy == l_corner && len == 1)
		return (r_in);
	else if (sy == l_corner && len == 2)
		return (heredoc);
	else if (sy == r_corner && len == 1)
		return (r_out);
	else if (sy == r_corner && len == 2)
		return (r_append);
	else if (sy == pipes)
		return (lpipe);
	return (word);
}

inline int	get_skip_distance(char *sy, int len)
{
	char	*tmp;

	tmp = sy;
	if (*tmp == s_quote || *tmp == d_quote)
		return (len + 2);
	else if (*tmp == l_corner || *tmp == r_corner)
	{
		if (*tmp == *(tmp + 1))
			return (2);
		return (1);
	}
	return (len);
}
