#include "minishell.h"

void	exec_last_cmd(t_env *env, t_cmd *cmd)
{
	printf("{cmd=%s, args=%d, in=%d, out=%d}\n",
		   cmd->name, cmd->counter.words - 1, cmd->counter.in, cmd->counter
				   .out);
}