/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 01:21:26 by refrain           #+#    #+#             */
/*   Updated: 2022/10/03 08:59:41 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrlc_handler(void)
{
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	slash_handler_util(int signal)
{
	int		pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signal == SIGQUIT)
		write(1, "Quit: 3\n", 8);
	if (signal == SIGINT)
	{
		if (!pid)
			write(1, "\n", 1);
		if (pid)
		{
			rl_on_new_line();
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}	
}

static void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("\nheredoc> ", STDIN_FILENO);
}

static void	echo_ctl(char on)
{
	struct termios	tstate;

	tcgetattr(0, &tstate);
	if (on)
		tstate.c_lflag |= ECHOCTL;
	else
		tstate.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tstate);
}

void	signal_handler(t_signal_type code)
{
	echo_ctl(0);
	if (code == sig_loop)
	{
		signal(SIGINT, (void *)ctrlc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (code == sig_child)
	{
		signal(SIGQUIT, (void *)slash_handler_util);
		signal(SIGINT, (void *)slash_handler_util);
	}
	else if (code == sig_heredoc)
	{
		signal(SIGINT, (void *)heredoc_handler);
		signal(SIGQUIT, (void *)heredoc_handler);
	}
}
