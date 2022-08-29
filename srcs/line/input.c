#include "minishell.h"

static inline void	ft_load_history(t_sh *args)
{
	int		res;
	char	*line;

	// args->fd = open(HISTORY_FILE, O_CREAT | O_APPEND | O_RDWR, 0664);
	// if (args->fd < 0)
	// {
		// print_err(MSG_ERR_INVAL_HIS_FD, NULL, false);
		// return ;
	// }
	line = NULL;
	// load_history(HISTORY_FILE);
	// while (true)
	// {
	// 	res = ft_gnl(args->fd, &line);
	// 	if (res > 0)
	// 		add_history(line);
	// 	else if (res <= 0)
	// 	{
	// 		free(line);
	// 		break ;
	// 	}
	// 	free(line);
	// 	line = NULL;
	// }
}

void	init_shell(t_sh *sh, t_env *env)
{
	int	cur_level;

	sh->env = env;
	sh->exit_status = 0;
	cur_level = ft_atoi(get_env_value("SHLVL", sh->env));
	sh->level = cur_level + 1;
	read_history(HISTORY_FILE);
}

void	start_shell(t_sh *sh)
{
	char	*line;
	char	*prefix;
	char	*tmp;

	while(1)
	{
		prefix = ft_strjoin(DEFAULT_PREFIX, get_env_value("PWD", sh->env));
		tmp = prefix;
		prefix = ft_strjoin(tmp, DOLLAR);
		free(tmp);
		line = readline(prefix);
		free(prefix);
		add_history(line);
		write_history(HISTORY_FILE);
	}
}