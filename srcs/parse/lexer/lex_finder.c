#include "minishell.h"

static int	find_symbol(char *ptr, char sy)
{
	int	distance;

	distance = -1;
	// добавить обработку не той ковычки
	while (ptr[++distance])
		if (ptr[distance] == sy)
			return (distance);
	return (trigger_unclosed_quote_error(sy));
}

static int	find_separator(char *ptr)
{
	int		distance;
	int		cur;

	distance = 0;
	while (ptr[distance++])
	{
		cur = ptr[distance];
		if (cur == tab || cur == endl
			|| cur == vtab || cur == cr || cur == space)
			return (distance);
	}
	if (distance > 0 && cur == 0)
		return (distance - 1);
	return (-1);
}

int	find_end(char *ptr)
{
	int	d;

	if (*ptr == s_quote)
		return (find_symbol(ptr + 1, s_quote));
	else if (*ptr == d_quote)
		return (find_symbol(ptr + 1, d_quote));
	else if (*ptr == r_corner || *ptr == l_corner)
	{
		if (*ptr == *(ptr + 1))
			return (2);
		return (1);
	}
	return (find_separator(ptr));
}