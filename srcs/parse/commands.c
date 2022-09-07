#include "minishell.h"

t_cmd	*create_commands(t_token *tokens)
{
	t_count counter;

	counter = count_entities(tokens);
	printf("in=%d out=%d words=%d\n", counter.in, counter.out, counter.words);
}