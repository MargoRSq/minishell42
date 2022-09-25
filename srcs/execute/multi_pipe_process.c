#include "minishell.h"

void	multi_pipe_process(t_env *env, t_cmd *cmd)
{
	printf("multi_pipe\n");
	while (cmd != NULL)
	{

		cmd = cmd->next;
	}
}