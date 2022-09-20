#include "minishell.h"


static void	inline skip_arg(char *str, int *iptr)
{

}

static int	get_code(int sy, int len)
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

static inline int	move(char sy, int len)
{
	switch ((int)sy)
	{
	case s_quote: case d_quote:
		return (len + 1);
	default:
		return (len);
	}
}

static inline int	get_skip_distance(char *sy, int len)
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


static inline int counter_skip_single_quote(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i] != '\'')
		len++;
	return (len);
}

static int inline counter_skip_unpacked_env(char *str, t_env *env)
{
	int		i;
	int		len;
	char	*var_key;
	char	*var_value;

	i = -1;
	len = 0;
	while (str[++i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '$')
		len++;
	var_key = ft_substr(str, 0, len);
	var_value = get_env_value(var_key, env);
	// *(iptr) += ft_strlen(var_key);
		return (ft_strlen(var_value));	
	return (0);
}

static inline int count_final_len(char *str, int len, short is_dq, t_env *env)
{
	int	i;
	int	final_len;
	int	tmp;

	final_len = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'')
		{
			tmp = counter_skip_single_quote(&str[i + 1]) ;
			final_len += tmp;
			if (is_dq)
				final_len += 2;
			i += tmp + 1;
		}
		else if (str[i] == '$')
		{
			tmp = counter_skip_unpacked_env(&str[i + 1], env);
			final_len += tmp;
			i++;
			while (i < len && str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '$')
				i++;
		}
		else
		{
			i++;
			final_len++;
		}
	}
	return (final_len);
}

static char	*fetch_envstr(char *str, int pos, t_env *env)
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

static int	ft_envcpy(char *start, int pos, char *new_start, t_env *env)
{
	int		elen;
	char	*evar;

	evar = fetch_envstr(start, pos, env);
	elen = ft_strlen(evar);
	if (elen)
		ft_strlcpy(new_start, evar, elen + 1);
	return (elen);
}

static inline char	*unpack(char *str, int len, int final_len, short is_dq, t_env *env)
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
			tmp = counter_skip_single_quote(&str[i + 1]);
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

static t_token	*unpack_tmp_token(t_tmp tkn, t_env *env)
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

t_token	*lex_line(char *line, t_env *env)
{
	int		i;
	int		len;
	int		code;
	t_token	*tokens;
	t_token	*token;
	t_tmp	tkn;
	int		sep;

	i = 0;
	sep = 0;
	tokens = NULL;
	while (line[i])
	{
		if (line[i] == space)
		{
			i++;
			sep = 1;
		}
		else
		{
			len = find_end(&line[i]);
			if (len == -1)
				return (NULL);
			code = get_code((int)line[i], len);
			if (code == word)
				tkn = (t_tmp){.len=len, .sep=sep, .type=0, .str=&line[i]};
			else if (code == d_quote_str)
				tkn = (t_tmp){.len=len, .sep=sep, .type=1, .str=&line[i + 1]};
			else if (code == s_quote_str)
				tkn = (t_tmp){.len=len, .sep=sep, .type=2, .str=&line[i + 1]};
			else
				tkn = (t_tmp){.len=len, .tmp_code=code, .type=3, .str=&line[i]};
			token = unpack_tmp_token(tkn, env);
			tokenlst_add_back(&tokens, token);
			i += get_skip_distance(&line[i], len);
			sep = 0;
		}
	}
	tokenlst_print(tokens);
	return (tokens);
}
