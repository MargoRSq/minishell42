#include "minishell.h"

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

static int inline counter_skip_unpacked_env(char *str, t_env *env, int *iptr)
{
	int		i;
	int		len;
	char	*var_key;
	char	*var_value;

	i = -1;
	len = 0;
	while (str[++i] != '\'' && str[i] != '\"' && str[i] != ' ')
		len++;
	var_key = ft_substr(str, 0, len);
	var_value = get_env_value(var_key, env);
	*(iptr) += ft_strlen(var_key);
		return (ft_strlen(var_value));	
	return (0);
}

static inline int count_final_len(char *str, int len, short is_dq, t_env *env)
{
	int	i;
	int	final_len;
	int	tmp;

	final_len = 0;
	i = -1;
	while (++i < len)
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
			tmp = counter_skip_unpacked_env(&str[i + 1], env, &i);
			final_len += tmp;
		}
		else
			final_len++;
	}
	return (final_len);
}

static t_token	*unpack_qoutes(char *start, int len, t_env *env)
{
	int	dollars;
	int	i;
	int	final_len;


	final_len = count_final_len(start, len, 1, env);
	printf("%d\n", final_len);

	// dollars = count_len_dollars(start, len);

	return (NULL);
	       
	
}

t_token	*lex_line(char *line, t_env *env)
{
	int		i;
	int		len;
	int		code;
	t_token	*tokens;
	t_token	*token;
	int		sep;

	i = 0;
	sep = 0;
	tokens = NULL;
	while (line[i])
	{
		if (line[i] == space)
			i++;
		else
		{
			len = find_end(&line[i]);
			if (len == -1)
				return (NULL);
			code = get_code((int)line[i], len);
			// if (code == word)
				// token = unpack_string(&line[i], len);
			// else if (code == s_quote_str)
			if (code == d_quote_str)
				token = unpack_qoutes(&line[i + 1], len, env);
			// else 
			token = tokenlst_new(&line[i], len, code);
			tokenlst_add_back(&tokens, token);
			i += get_skip_distance(&line[i], len);
		}
	}
	tokenlst_print(tokens);
	return (tokens);
}
