/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:14 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/09 16:42:29 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static inline void	load_history()
{
	int		res;
	char	*line;
	int		fd;

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

void	init_shell(t_list *envlst)
{
	char	*cur_level;

	cur_level = get_env_value("SHLVL", envlst);
	if (cur_level)
		g_status.shell_level = ft_atoi(cur_level) + 1;
	else
		g_status.shell_level = 1;
	load_history();
}
static char	*launch_readline()
{
	char	*tmp;
	char	*prefix;
	char	*line;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	prefix = ft_strjoin(DEFAULT_PREFIX, pwd);
	if (!prefix)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
	tmp = prefix;
	prefix = ft_strjoin(tmp, DOLLAR);
	if (!prefix)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, malloc_error, 1));
	free(tmp);
	line = readline(prefix);
	free(prefix);
	free(pwd);
	return (line);
}
static char	*get_entered_line()
{
	char	*entered_line;

	entered_line = launch_readline();
	if (ft_strlen(entered_line) > 0)
	{
		add_history(entered_line);
		ft_putstr_fd(entered_line, g_status.rl_fd);
		ft_putchar_fd('\n', g_status.rl_fd);
	}
	return (entered_line);
}

void	start_shell(t_list **envlst)
{
	char		*line;
	t_list		*tokens;
	t_list		*cmds;

	while (!g_status.interrupt)
	{
		line = get_entered_line();
		if (!line || !(*line))
			continue ;
		if (g_status.interrupt)
			break ;
		tokens = lex_line(line, *envlst);
		if (!tokens)
			continue ;
		if (g_status.interrupt)
			break ;
		check_tokens(tokens, *envlst);
		if (g_status.interrupt)
			break ;
		cmds = create_commands(tokens);
		if (g_status.interrupt)
			break ;
		execute(envlst, cmds);
		free(line);
		clean_tokens_cmds(cmds, tokens);
	}
	ft_lstclear(envlst, envlst_delete_elem);
}
