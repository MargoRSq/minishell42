/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:49:15 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/12 19:14:57 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_with_message(void)
{
	if (g_status.exit_msg)
		printf("%s", g_status.exit_msg);
	else
		printf("Goodbye!\n");
	return (g_status.exit_code);
}

static void	init_status(void)
{
	g_status.exit_code = 0;
	g_status.exit_msg = NULL;
	g_status.interrupt = 0;
}

static inline void	load_history(void)
{
	char	*line;

	g_status.rl_fd = open(HISTORY_FILE, O_CREAT | O_APPEND | O_RDWR, 0664);
	if (g_status.rl_fd < 0)
		return (error_msg_return_void(MSG_ERR_RL_FD, NULL, malloc_error, 1));
	line = NULL;
	while (1)
	{
		line = get_next_line(g_status.rl_fd);
		if (line)
			add_history(line);
		else
		{
			free(line);
			break ;
		}
		free(line);
		line = NULL;
	}
}

static void	init_shell(t_list *envlst)
{
	char	*cur_level;

	cur_level = get_env_value("SHLVL", envlst);
	if (cur_level)
	{
		g_status.shell_level = ft_atoi(cur_level) + 1;
		change_or_append(envlst, ft_strdup("SHLVL"),
			ft_itoa(g_status.shell_level));
	}
	else
		g_status.shell_level = 1;
	load_history();
}

int	main(int ac, char **av, char **envp)
{
	t_list	*envlst;

	(void)av;
	if (ac != 1)
		return (1);
	init_status();
	envlst = parse_envp(envp);
	init_shell(envlst);
	start_shell(&envlst);
	return (exit_with_message());
}
