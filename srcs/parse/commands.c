#include "minishell.h"


t_cmd	*create_commands(t_token *tokens)
{
	t_count counter;
	t_cmd	*cmds;

	cmds = NULL;
	// while (tokens)
	// {
	cmdlst_add_back(&cmds, cmdlst_new(tokens));
	cmdlst_print(cmds);
		// while (tokens && tokens->code != lpipe)
		// 	tokens = tokens->next;
		// tokens = tokens->next;
	// }
}