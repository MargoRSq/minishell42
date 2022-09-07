#include "minishell.h"


static int inline count_in_files(t_token *tokens)
{
	int		counter;
	t_token	*tmp;

	counter = 0;
	tmp = tokens;
	while (tmp && tmp->code != lpipe)
	{
		if (tmp->code == r_in)
		{
			counter++;
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break;
		}
		tmp = tmp->next;
	}
	return (counter);
}

static int inline	count_out_files(t_token *tokens)
{
	int		counter;
	t_token	*tmp;

	counter = 0;
	tmp = tokens;
	while (tmp && tmp->code != lpipe)
	{
		if (tmp->code == r_out || tmp->code == r_append)
		{
			counter++;
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break;
		}
		tmp = tmp->next;
	}
	return (counter);
}

static int inline count_words(t_token *tokens)
{
	int		counter;
	t_token	*tmp;

	counter = 0;
	tmp = tokens;
	while (tmp && tmp->code != lpipe)
	{
		if (tmp->code == r_out || tmp->code == r_append || tmp->code == r_in)
		{
			if (tmp->next && tmp->next->next)
				tmp = tmp->next->next;
			else
				break;
		}
		else 
		{
			counter++;
			tmp = tmp->next;
		}
	}
	return (counter);
}

t_count	count_entities(t_token *tokens)
{
	t_count	counter;

	counter.in = count_in_files(tokens);
	counter.out = count_out_files(tokens);
	counter.words = count_words(tokens);
	return (counter);
}

