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

static t_token	*parse_quotes(t_token *last, char *line, int i)
{
	
}

t_token	*lex_line(char *line)
{
	int		i;
	int		len;
	int		code;
	t_token	*tokens;
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
			if (len == -1)
				return (NULL);
			code = get_code((int)line[i], len);
			if (code == d_quote_str || code == s_quote_str)
				token = parse_quotes(tokenlst_last(tokens), line, i);
			else 
				token = tokenlst_new(&line[i], len, code);
			tokenlst_add_back(&tokens, token);
			i += get_skip_distance(&line[i], len);
		}
	}
	// tokenlst_print(tokens);
	return (tokens);
}
