#include "minishell.h"

void	init_shell(t_sh *sh, t_env *env)
{
	char	*cur_level;

	sh->env = env;
	sh->exit_status = 0;
	cur_level = get_env_value("SHLVL", sh->env);
	if (cur_level)
		sh->level = ft_atoi(cur_level) + 1;
	else
		sh->level = 1;
	read_history(HISTORY_FILE);
}

static char	*launch_readline(t_env *env)
{
	char	*tmp;
	char	*prefix;
	char	*line;

	prefix = ft_strjoin(DEFAULT_PREFIX, get_env_value("PWD", env));
	if (!prefix)
		return (trigger_malloc_error());
	tmp = prefix;
	prefix = ft_strjoin(tmp, DOLLAR);
	if (!prefix)
		return (trigger_malloc_error());
	free(tmp);
	line = readline(prefix);
	free(prefix);
	return (line);
}

static char	*get_entered_line(t_sh *sh)
{
	char	*entered_line;

	entered_line = launch_readline(sh->env);
	add_history(entered_line);
	write_history(HISTORY_FILE);
	return (entered_line);
}

void	start_shell(t_sh *sh)
{
	char		*line;
	t_token		*tokens;

	while(1)
	{
		line = get_entered_line(sh);
		if (g_status.interrupt)
			break ;
		tokens = lex_line(line);
		if (g_status.interrupt)
			break ;
	}
}