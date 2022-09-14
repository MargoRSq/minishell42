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

t_token	*lex_line(char *line)
{
	int		i;
	int		len;
	int		code;
	t_token	*tokens;

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
			tokenlst_add_back(&tokens, tokenlst_new(&line[i], len, code));
			i += get_skip_distance(&line[i], len);
		}
	}
	// tokenlst_print(tokens);
	return (tokens);
}
