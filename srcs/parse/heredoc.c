#include "minishell.h"

static int	ft_heredoc(char *path_tmp, t_token *infile);
static char	*create_filename_heredoc(char *path_tmp);
static char	*join_path_index(char *path_tmp, int i);
static int	get_next_line_heredoc(char *stop, int fd);


static void	ft_close_file(int fd, char *name)
{
	if (close(fd) == -1)
		printf("asdas");
		// ft_print_error(name, strerror(errno));
}


static char	*get_path_tmp(t_env *env)
{
	char	*path_tmp;
	char	*value_tmp;
	char	*pwd;
	char	*index;
	int		i;
	char	*try;

	path_tmp = NULL;
	try = NULL;
	pwd = get_cur_dir(env);
	if (!pwd)
		return (error_msg_return_charz(MSG_ERR_ENV, env_error, 1));
	path_tmp = ft_strjoin(pwd, TMP_FILE_PREFIX);
	if (!path_tmp)
		return (error_msg_return_charz(MSG_ERR_MEM, env_error, 1));
	i = -1;
	int tmp;
	index = ft_itoa(++i);
	if (!index)
		return NULL;
	try = ft_strjoin(path_tmp, index);
	while (access(try, F_OK) > -1)
	{
		free(try);
		index = ft_itoa(++i);
		try = ft_strjoin(path_tmp, index);
		free(index);
	}
	free(path_tmp);
	return (try);
}


int	open_heredoc(t_token *token, t_env *env)
{
	char		*path_tmp;

	path_tmp = get_path_tmp(env);
	if (!path_tmp)
		return (1);
	if (ft_heredoc(path_tmp, token))
	{
		free(path_tmp);
		return (EXIT_FAILURE);
	}
	// free(path_tmp);
	return (EXIT_SUCCESS);
}

static int	ft_heredoc(char *path_tmp, t_token *infile)
{
	char	*filename;
	char	*stop;
	int		fd;

	// filename = create_filename_heredoc(path_tmp);
	// if (!filename)
		// return (EXIT_FAILURE);
	fd = open(path_tmp, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		free(filename);
		return (EXIT_FAILURE);
	}
	stop = ft_substr(infile->start, 0, infile->len);
	if (get_next_line_heredoc(stop, fd))
	{
		ft_close_file(fd, stop);
		free(filename);
		return (EXIT_FAILURE);
	}
	free(stop);
	infile->start = path_tmp;
	infile->len = ft_strlen(path_tmp);
	return (EXIT_SUCCESS);
}

static char	*create_filename_heredoc(char *path_tmp)
{
	int		i;
	char	*name;

	i = 0;
	while (1)
	{
		name = join_path_index(path_tmp, i);
		if (access(name, F_OK | W_OK) == -1)
			break ;
		free(name);
		i++;
	}
	return (name);
}

static char	*join_path_index(char *path_tmp, int i)
{
	char	*index;
	char	*name_index;
	char	*path_name;

	index = NULL;
	name_index = NULL;
	path_name = NULL;
	index = ft_itoa(i);
	if (!index)
		return (NULL);
	name_index = ft_strjoin(".minishell_heredoc_", index);
	free(index);
	if (!name_index)
		return (NULL);
	path_name = ft_strjoin(path_tmp, name_index);
	free(name_index);
	return (path_name);
}

static void	heredoc_handler_util(int signal)
{
	int		pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
	}
	if (signal == SIGINT)
	{
		if (!pid)
			write(1, "\n", 1);
		if (pid)
		{
			write(1, "\n", 1);
			// rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
	exit (1);
}

static void	signal_handler_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (void *)heredoc_handler_util);
}

static int	get_next_line_heredoc(char *stop, int fd)
{
	char	*line;
	int		len_limiter;

	len_limiter = ft_strlen(stop);
	while (1)
	{
		signal_handler_heredoc();
		ft_putstr_fd(">", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (EXIT_SUCCESS);
		if (ft_strcmp(line, stop) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	return (EXIT_SUCCESS);
}
