#include "minishell.h"

static t_token	*create_token(char *line, int pos, int len, int sep, t_env *env)
{
	t_tmp	tkn;
	int		code;

	if (len == -1)
		return (NULL);
	code = get_code((int)line[pos], len);
	tkn = create_tmp_token(len, code, sep, line, pos);
	return (unpack_tmp_token(tkn, env));
}

t_token	*lex_line(char *line, t_env *env)
{
	int		i;
	int		len;
	t_token	*tokens;
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
			tokenlst_add_back(&tokens, create_token(line, i, len, sep, env));
			i += get_skip_distance(&line[i], len);
			sep = 0;
		}
	}
	// tokenlst_print(tokens);
	return (tokens);
}
