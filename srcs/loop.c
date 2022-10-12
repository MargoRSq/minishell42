/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:14 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/12 19:14:19 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*launch_readline(void)
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
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	tmp = prefix;
	prefix = ft_strjoin(tmp, DOLLAR);
	if (!prefix)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	free(tmp);
	line = readline(prefix);
	if (line == NULL)
		exit(0);
	free(prefix);
	free(pwd);
	return (line);
}

static char	*get_entered_line(void)
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

void	execute_and_clean(t_list **envlst, char *line, t_list *cmds,
	t_list *tokens)
{
	if (g_status.interrupt)
		return ;
	execute(envlst, cmds);
	free(line);
	clean_tokens_cmds(cmds, tokens);
}

void	start_shell(t_list **envlst)
{
	char		*line;
	t_list		*tokens;
	t_list		*cmds;

	while (!g_status.interrupt)
	{
		signal_handler(sig_loop);
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
		check_tokens(tokens);
		if (g_status.interrupt)
			break ;
		cmds = create_commands(tokens);
		execute_and_clean(envlst, line, cmds, tokens);
	}
	ft_lstclear(envlst, envlst_delete_elem);
}
