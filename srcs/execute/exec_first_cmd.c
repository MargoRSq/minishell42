#include "minishell.h"

void	exec_first_cmd(t_list *envlst, t_cmd *cmd)
{
	printf("{cmd=%s, args=%d, in=%d, out=%d}\n",
		   cmd->argv[0], cmd->counter.words - 1, cmd->counter.in, cmd->counter
		   .out);
}