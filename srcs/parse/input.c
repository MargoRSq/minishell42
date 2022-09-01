#include "minishell.h"

void	init_shell(t_sh *sh, t_env *env)
{
	int	cur_level;

	sh->env = env;
	sh->exit_status = 0;
	cur_level = ft_atoi(get_env_value("SHLVL", sh->env));
	sh->level = cur_level + 1;
	read_history(HISTORY_FILE);
}

static inline char	*get_line(t_sh *sh)
{
	char	*line;
	char	*tmp;
	char	*prefix;

	prefix = ft_strjoin(DEFAULT_PREFIX, get_env_value("PWD", sh->env));
	tmp = prefix;
	prefix = ft_strjoin(tmp, DOLLAR);
	free(tmp);
	line = readline(prefix);
	free(prefix);
	add_history(line);
	write_history(HISTORY_FILE);
	return (line);

}

void	start_shell(t_sh *sh)
{
	char	*line;

	while(1)
	{
		line = get_line(sh);
		lex_line(line);
	}
}