#include "minishell.h"

int	get_code(char sy, int len)
{
	if ((int)sy == s_quote)
		return (s_quote_str);
	else if ((int)sy == d_quote)
		return (d_quote_str);
	else if ((int)sy == l_corner && len == 1)
		return (r_in);
	else if ((int)sy == l_corner && len == 2)
		return (heredoc);
	else if ((int)sy == r_corner && len == 1)
		return (r_out);
	else if ((int)sy == r_corner && len == 2)
		return (r_append);
	return (word);
}

t_token	*lex_line(char *line)
{
	int		i;
	int		len;
	int		code;
	int		until;
	t_token	*tokens;
	// t_token	*tmp;

	i = -1;
	tokens = NULL;
	until = ft_strlen(line);
	len = 0;
	while (++i < until - 1)
	{
		while (&line[i] == space)
			i++;
		len = find_end(&line[i]);
		code = get_code(line[i], len);
		tokenlst_add_back(&tokens, tokenlst_new(&line[i], len, code));
		i+=len;
	}
	tokenlst_print(tokens);
}
