#include "minishell.h"


char	*fetch_envstr(char *str, int pos, t_env *env)
{
	int		key_len;
	int		i;
	char	*key; // free
	char	*value; //free

	key_len = 0;
	i = -1;
	while (str[++i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '$')
		key_len++;
	key = ft_substr(str, 0, key_len);
	value = get_env_value(key, env);
	return (value);
}

int	ft_envcpy(char *start, int pos, char *new_start, t_env *env)
{
	int		elen;
	char	*evar;

	evar = fetch_envstr(start, pos, env);
	elen = ft_strlen(evar);
	if (elen)
		ft_strlcpy(new_start, evar, elen + 1);
	return (elen);
}

static void	fill_new_str(int tmp, int len, t_cpy cpy, t_env *env)
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
		tmp = ft_envcpy(&cpy.src[(*cpy.ir) + 1], (*cpy.jr),
				&cpy.dst[(*cpy.jr)], env);
		(*cpy.jr) += tmp;
		(*cpy.ir)++;
		while ((*cpy.ir) < len && cpy.src[(*cpy.ir)] != ' '
			&& cpy.src[(*cpy.ir)] != '$' && cpy.src[(*cpy.ir)] != '\'')
			(*cpy.ir)++;
	}
	else
		cpy.dst[(*cpy.jr)++] = cpy.src[(*cpy.ir)++];
}

char	*unpack(char *str, t_len lns, short is_dq, t_env *env)
{
	int		i;
	int		j;
	int		tmp;
	t_cpy	cpy;
	char	*new;

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
		fill_new_str(tmp, lns.len, cpy, env);
	}
	return (new);
}