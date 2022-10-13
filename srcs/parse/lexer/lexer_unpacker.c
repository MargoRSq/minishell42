/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_unpacker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:32:16 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/13 15:19:43 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *key, t_list *envlst)
{
	char	*value;

	value = NULL;
	if (ft_strcmp(key, "$") == 0)
	{
		value = (char *)malloc(sizeof(char) * 3);
		ft_strlcpy(value, "$$", 3);
	}
	else if (ft_strcmp(key, "?") == 0)
		value = ft_itoa(g_status.exit_code);
	else
		value = ft_strdup(get_env_value(key, envlst));
	return (value);
}

char	*fetch_envstr(char *str, t_list *envlst)
{
	int		key_len;
	int		i;
	char	*key;
	char	*value;

	key_len = 0;
	i = -1;
	while (str[++i] != '\'' && str[i] != '\"' && str[i] != ' '
		&& (str[i] != '$') && str[i])
		key_len++;
	if (key_len == 0 && str[i] == '$')
		key = ft_strdup("$");
	else
		key = ft_substr(str, 0, key_len);
	value = get_value(key, envlst);
	free(key);
	return (value);
}

int	ft_envcpy(char *start, char *new_start, t_list *envlst)
{
	int		elen;
	char	*evar;

	evar = fetch_envstr(start, envlst);
	elen = ft_strlen(evar);
	if (elen)
		ft_strlcpy(new_start, evar, elen + 1);
	free(evar);
	return (elen);
}

static void	fill_new_str(int tmp, int len, t_cpy cpy, t_list *envlst)
{
	if (cpy.tp == 0)
	{
		if (cpy.is_dq)
			cpy.dst[(*cpy.jr)++] = '\'';
		tmp = counter_str_single_quote(&cpy.src[(*cpy.ir) + 1]);
		ft_strlcpy(&cpy.dst[(*cpy.jr)], &cpy.src[(*cpy.ir) + 1], tmp + 1);
		(*cpy.ir) += tmp + 1 + cpy.is_dq;
		(*cpy.jr) += tmp;
		if (cpy.is_dq)
			cpy.dst[(*cpy.jr)++] = '\'';
	}
	else if (cpy.tp == 1)
	{
		tmp = ft_envcpy(&cpy.src[(*cpy.ir) + 1],
				&cpy.dst[(*cpy.jr)], envlst);
		(*cpy.jr) += tmp;
		(*cpy.ir)++;
		while ((*cpy.ir) < len && cpy.src[(*cpy.ir)] != ' '
			&& cpy.src[(*cpy.ir) + 1] != '$' && cpy.src[(*cpy.ir)] != '\'')
			(*cpy.ir)++;
	}
	else
		cpy.dst[(*cpy.jr)++] = cpy.src[(*cpy.ir)++];
}

char	*unpack(char *str, t_len lns, short is_dq, t_list *envlst)
{
	int		i;
	int		j;
	int		tmp;
	t_cpy	cpy;
	char	*new;

	tmp = 0;
	new = (char *)malloc(sizeof(char) * lns.final_len + 1);
	if (!new)
		return (NULL);
	new[lns.final_len] = '\0';
	i = 0;
	j = 0;
	while (i < lns.len)
	{
		if (str[i] == '\'')
			cpy = (t_cpy){.dst = new, .src = str, .ir = &i, .jr = &j,
				.is_dq = is_dq, .tp = 0};
		else if (str[i] == '$')
			cpy = (t_cpy){.dst = new, .src = str, .ir = &i, .jr = &j, .tp = 1};
		else
			cpy = (t_cpy){.dst = new, .src = str, .ir = &i, .jr = &j, .tp = 2};
		fill_new_str(tmp, lns.len, cpy, envlst);
	}
	return (new);
}
