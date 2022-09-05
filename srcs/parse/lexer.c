#include "minishell.h"

int	get_code(char sy, int len)
{
	switch ( (int)sy )
	{
		case s_quote:
			return (s_quote_str);
		case d_quote_str:
			return (s_quote_str);
		case (l_corner):
			if (len == 1)
				return (r_in);
			else if (len == 2)
				return (heredoc);
		case (r_corner):
			if (len == 1)
				return (r_out);
			else if (len == 2)
				return (r_append);
	}
	return (word);
	// if ((int)sy == s_quote)
	// else if ((int)sy == d_quote)
	// 	return (d_quote_str);
	// else if ((int)sy == l_corner && len == 1)
	// else if ((int)sy == l_corner && len == 2)
	// 	return (heredoc);
	// else if ((int)sy == r_corner && len == 1)
	// 	return (r_out);
	// else if ((int)sy == r_corner && len == 2)
	// 	return (r_append);
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

t_token	*lex_line(char *line)
{
	int		i;
	int		len;
	int		code;
	int		until;
	t_token	*tokens;
	// t_token	*tmp;

	i = 0;
	tokens = NULL;
	until = ft_strlen(line);
	len = 0;
	while (line[i])
	{
		if (line[i] == space)
			i++;
		else
		{
			len = find_end(&line[i]);
			code = get_code(line[i], len);
			tokenlst_add_back(&tokens, tokenlst_new(&line[i], len, code));
			i+=move(code, len);
		}
	}
	tokenlst_print(tokens);
}
