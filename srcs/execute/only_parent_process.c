#include "minishell.h"

void	only_parent_process(t_env *env, t_cmd *cmd)
{
	printf("parent\n");
	if (cmd->name)
		try_builtin(cmd, env);

}