#include "minishell.h"

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

void	signal_handler_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (void *)heredoc_handler_util);
}