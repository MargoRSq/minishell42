#include "minishell.h"

int main(int ac, char **av, char **env)
{
	char *line;
	(void)ac; (void)av; (void)env;

	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		line = readline("\e[1;34mmaybach$ \e[0;37m");
		printf("---%s---\n", line);
		add_history(line);
	}
	return (0);
}
