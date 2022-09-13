#include "minishell.h"

static int try_builtin(t_cmd *cmds, t_env *env)
{
	if (!ft_strcmp(cmds->name, "cd"))
		execute_cd(env, cmds->argv);
	else if (!ft_strcmp(cmds->name, "echo"))
		execute_echo(cmds->argv);
	else if (!ft_strcmp(cmds->name, "pwd"))
		execute_pwd(env);
	else if (!ft_strcmp(cmds->name, "env"))
		execute_env(env);
	else if (!ft_strcmp(cmds->name, "unset"))
		execute_unset(env, cmds->argv);
	return (1);	

}

void	execute(t_env *env, t_cmd *cmds)
{
	while (cmds != NULL)
	{
		try_builtin(cmds, env);
		cmds = cmds->next;
	}
}