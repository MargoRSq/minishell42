#include "minishell.h"

int try_builtin(t_cmd *cmds, t_env *env)
{
	if (!ft_strcmp(cmds->name, "cd") || !ft_strcmp(cmds->name, "CD"))
		execute_cd(env, cmds->argv);
	else if (!ft_strcmp(cmds->name, "echo") || !ft_strcmp(cmds->name, "ECHO"))
		execute_echo(cmds->argv);
	else if (!ft_strcmp(cmds->name, "pwd") || !ft_strcmp(cmds->name, "PWD"))
		execute_pwd(env);
	else if (!ft_strcmp(cmds->name, "env") || !ft_strcmp(cmds->name, "ENV"))
		execute_env(env);
	else if (!ft_strcmp(cmds->name, "unset") || !ft_strcmp(cmds->name, "UNSET"))
		execute_unset(env, cmds->argv);
	else if (!ft_strcmp(cmds->name, "exit") || !ft_strcmp(cmds->name, "EXIT"))
		execute_exit(env, cmds->argv);
	else if (!ft_strcmp(cmds->name, "export") || \
			!ft_strcmp(cmds->name, "EXPORT"))
		execute_export(env, cmds->argv);
	return (1);	
}

void	execute(t_env *env, t_cmd *cmd)
{
		cmdlst_print(cmd);
		if (cmd->next == NULL)
			only_parent_process(env, cmd);
		else
			multi_pipe_process(env, cmd);
}