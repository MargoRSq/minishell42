/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:32 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/09 19:03:49 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int inline	counter_skip_unpacked_env(char *str, t_list *envlst)
{
	int		i;
	int		len;
	char	*var_key;
	char	*var_value;

	i = -1;
	len = 0;
	while (str[++i] != '\'' && str[i] != '\"' && str[i] != ' '&& str[i] != '$')
		len++;
	if (len == 0 && str[i] == '$')
		len++;
	var_key = ft_substr(str, 0, len);
	var_value = get_value(var_key, envlst);
	len = ft_strlen(var_value);
	free(var_value);
	free(var_key);
	return (len);
}

int	counter_str_single_quote(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i] != '\'')
		len++;
	return (len);
}

inline int	skipper_str_single_quote(char *str, int *iptr, short is_dq)
{
	int	tmp;
	int	result;

	result = 0;
	tmp = counter_str_single_quote(&str[*(iptr) + 1]);
	result += tmp;
	if (is_dq)
		result += 2;
	*iptr += tmp + 1;
	return (result);
}

int	skipper_str_with_env(char *str, int *iptr, int len, t_list *envlst)
{
	int	tmp;
	int	result;

	result = 0;
	tmp = counter_skip_unpacked_env(&str[*(iptr) + 1], envlst);
	result += tmp;
	(*iptr)++;
	if (str[*(iptr)] == '$')
		(*iptr)++;
	while (*(iptr) < len && str[*(iptr)] != '\'' && str[*(iptr)] != '\"'
		&& str[*(iptr)] != ' ' 
		&& (str[*(iptr)] != '$'))
		(*iptr)++;
	return (result);
}

int	count_final_len(char *str, int len, short is_dq, t_list *envlst)
{
	int	i;
	int	final_len;

	final_len = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'')
			final_len += skipper_str_single_quote(str, &i, is_dq);
		else if (str[i] == '$')
			final_len += skipper_str_with_env(str, &i, len, envlst);
		else
		{
			i++;
			final_len++;
		}
	}
	return (final_len);
}
