/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:35:14 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/04 18:55:00 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_list *envlst)
{
	char	*cur_level;

	cur_level = get_env_value("SHLVL", envlst);
	if (cur_level)
		g_status.shell_level = ft_atoi(cur_level) + 1;
	else
		g_status.shell_level = 1;
	read_history(HISTORY_FILE);
}

static char	*launch_readline(t_list *envlst)
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
	return (line);
}

static char	*get_entered_line(t_list *envlst)
{
	char	*entered_line;

	entered_line = launch_readline(envlst);
	add_history(entered_line);
	write_history(HISTORY_FILE);
	return (entered_line);
}

void	start_shell(t_list **envlst)
{
	char		*line;
	t_list		*tokens;
	t_list		*cmds;

	while (!g_status.interrupt)
	{
		line = get_entered_line(*envlst);
		if (!line || !(*line))
			continue ;
		if (g_status.interrupt)
			break ;
		tokens = lex_line(line, *envlst);
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
		// clean_tokens_cmds(cmds, tokens);
	}
	ft_lstclear(envlst, envlst_delete_elem);
}
