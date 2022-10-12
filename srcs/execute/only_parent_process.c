#include "minishell.h"

int	check_builtin(char *cmd)
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
	cur_dir = getcwd(NULL, 0);
	result = ft_strjoin(ways_with_dot, cur_dir);
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

void	bin_run(t_list **envlst, t_list *cmdlst)
{
	int 	fd;
	char	*bin;
	t_cmd	*cmd;

	cmd = cmdlst->content;
	fd = fork();
	if (fd == 0)
	{
		bin = get_cmd(*envlst, cmd->argv[0]);
		if (bin)
			execve(bin, cmd->argv, envlst_to_arr(*envlst));
		else
		{
			return (error_msg_return_void(MSG_ERR_CMD_NF, cmd->argv[0],
										  execve_error, 0));
		}
	}
	else
		wait(0);
}

void	only_parent_process(t_list **envlst, t_list *cmdlst)
{
	t_cmd	*cmd;
	int		in_fd;
	int		out_fd;

	cmd = cmdlst->content;
	if (cmd->argv[0])
	{
		if (cmd->infile)
		{
			in_fd = open(cmd->infile->name, O_RDONLY);
			dup2(in_fd, STDIN_FILENO);
		}
		if (cmd->outfile)
		{
			printf("here->>>\n");
			out_fd = open(cmd->outfile->name, O_RDWR | O_CREAT,
						  S_IWUSR | S_IRUSR);
			dup2(out_fd, STDOUT_FILENO);
		}
		if (check_builtin(cmd->argv[0]))
			try_builtin(cmd, envlst);
		else
			bin_run(envlst, cmdlst);
	}
}