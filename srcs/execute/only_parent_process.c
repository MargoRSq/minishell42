#include "minishell.h"

static int	check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "ECHO") || \
			!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "CD") || \
			!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "PWD") || \
			!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "EXPORT") || \
			!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "UNSET") || \
			!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "ENV") || \
			!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "EXIT"))
		return (1);
	else
		return (0);
}

char	*get_cmd(t_env *env, char *cmd)
{
	char	*command;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	paths = ft_split(get_env_value("PATH", env), ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(command, X_OK))
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	only_parent_process(t_env *env, t_cmd *cmd)
{
	int		fd;

	if (cmd->name)
	{
		if (check_builtin(cmd->name))
			try_builtin(cmd, env);
		 else
		{
			fd = fork();
			if (fd == 0)
				execve(get_cmd(env, cmd->name), cmd->argv, envlst_to_arr(env));
			else
				wait(0);
		}
	}



}