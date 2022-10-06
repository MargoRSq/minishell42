#include "minishell.h"

// typedef int	(*t_bldin_func)(t_env **, char **);

int	try_builtin(t_cmd *cmds, t_list **envlst)
{
	// const t_bldin_func	a_bldin_f[] = {execute_cd, execute_echo, execute_pwd, \
	// 	execute_unset, execute_exit, execute_export, \
	// 	execute_pwd, execute_env };
	if (!ft_strcmp(cmds->argv[0], "cd"))
		execute_cd(*envlst, cmds->argv);
	else if (!ft_strcmp(cmds->argv[0], "echo"))
		execute_echo(cmds->argv);
	else if (!ft_strcmp(cmds->argv[0], "pwd"))
		execute_pwd(*envlst);
	else if (!ft_strcmp(cmds->argv[0], "env"))
		execute_env(*envlst, cmds->argv);
	else if (!ft_strcmp(cmds->argv[0], "unset"))
		execute_unset(envlst, cmds->argv);
	else if (!ft_strcmp(cmds->argv[0], "exit"))
		execute_exit(cmds->argv);
	else if (!ft_strcmp(cmds->argv[0], "export"))
		execute_export(*envlst, cmds->argv);
	return (1);	
}

void	execute(t_list **envlst, t_list *cmds)
{
	t_cmd	*command;
	t_list	*next;

	next = cmds->next;
	if (cmds->content)
		command = (t_cmd *)(cmds->content);
	if (next == NULL)
		only_parent_process(envlst, command);
	else
		multi_pipe_process(envlst, command);
}