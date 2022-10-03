#include "minishell.h"

static int	check_builtin(char *cmd)
{
	if (cmd)
		ft_tolower(cmd);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
			!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
			!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
			!ft_strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}

char	*get_path(t_list *envlst)
{
	char	*result;
	char	*ways;
	char	*ways_with_dot;
	char	*cur_dir;

	ways = NULL;
	ways_with_dot = NULL;
	cur_dir = NULL;
	result = NULL;
	ways = get_env_value("PATH", envlst);
	ways_with_dot = ft_strjoin(ways, ":");
	cur_dir = get_cur_dir(envlst);
	result = ft_strjoin(ways_with_dot, cur_dir);
	free(ways);
	free(ways_with_dot);
	free(cur_dir);
	return (result);
}

char	*get_cmd(t_list *envlst, char *cmd)
{
	char	*command;
	char	*ways;
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	ways = get_path(envlst);
//	printf("PWD: %s\n", ways);
//	if (ways)
		paths = ft_split(ways, ':');
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

void	only_parent_process(t_list **envlst, t_cmd *cmd)
{
	int		fd;

	if (cmd->argv[0])
	{
		if (check_builtin(cmd->argv[0]))
			try_builtin(cmd, envlst);
		else
		{
			fd = fork();
			if (fd == 0)
			{
				execve(get_cmd(*envlst, cmd->argv[0]), cmd->argv,
					   envlst_to_arr(*envlst));
//				printf("error: %s\n", strerror(errno));
				error_msg_return_void(MSG_ERR_EXECVE, NULL, execve_error, 0);
//				printf("here\n");//this message we can't see after fatal in
//				execve!

				exit(execve_error);
			}
			else
				wait(0);
		}
	}



}