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

t_tmp	create_tmp_token(int len, int code, short sep, char *line, int pos)
{
	t_tmp	tkn;

	if (code == word)
		tkn = (t_tmp){.len=len, .sep=sep, .type=0, .str=&line[pos]};
	else if (code == d_quote_str)
		tkn = (t_tmp){.len=len, .sep=sep, .type=1, .str=&line[pos + 1]};
	else if (code == s_quote_str)
		tkn = (t_tmp){.len=len, .sep=sep, .type=2, .str=&line[pos + 1]};
	else
		tkn = (t_tmp){.len=len, .tmp_code=code, .type=3, .str=&line[pos]};
	return (tkn);
}

t_token	*unpack_tmp_token(t_tmp tkn, t_env *env)
{
	int		dollars;
	int		i;
	int		final_len;
	char	*new_start;


	if (tkn.type < 2)
	{
		final_len = count_final_len(tkn.str, tkn.len, tkn.type, env);
		// printf("%d\n", final_len);
		new_start = unpack(tkn.str, tkn.len, final_len, tkn.type, env);
		// printf("%s\n", new_start);
		return (tokenlst_new(new_start, final_len, word, tkn.sep));
	}
	else if (tkn.type == 2)
		return (tokenlst_new(tkn.str, tkn.len, word, tkn.sep));
	else
		return (tokenlst_new(tkn.str, tkn.len, tkn.tmp_code, tkn.sep));
}


char	*unpack(char *str, int len, int final_len, short is_dq, t_env *env)
{
	int	i;
	int	tmp;
	char	*new_start;

	i = 0;
	new_start = (char *)malloc(sizeof(char) * final_len + 1);
	if (!new_start)
		return (NULL);
	new_start[final_len] = '\0';
	int j = 0;
	while (i < len)
	{
		if (str[i] == '\'')
		{
			if (is_dq)
				new_start[j++] = '\'';
			tmp = counter_str_single_quote(&str[i + 1]);
			ft_strlcpy(&new_start[j], &str[i + 1], tmp + 1);
			i += tmp + 1 + is_dq;
			j += tmp;
			if (is_dq)
				new_start[j++] = '\'';
		}
		else if (str[i] == '$')
		{
			tmp = ft_envcpy(&str[i + 1], i, &new_start[j], env);
			j += tmp;
			i++;
			while (i < len && str[i] != ' ' && str[i] != '$' && str[i] != '\'')
				i++;
		}
		else
			new_start[j++] = str[i++];
	}
	return (new_start);
}
