/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:03:20 by svyatoslav        #+#    #+#             */
/*   Updated: 2022/10/12 19:04:42 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_tmp_filename_prefix(void)
{
	char	*filename_prefix;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	filename_prefix = ft_strjoin(pwd, TMP_FILE_PREFIX);
	free(pwd);
	if (!filename_prefix)
		return (NULL);
	return (filename_prefix);
}

static char	*create_tmp_filename(void)
{
	char	*filename_prefix;
	char	*index;
	int		i;
	char	*try;

	try = NULL;
	filename_prefix = create_tmp_filename_prefix();
	if (!filename_prefix)
		return (error_msg_return_charz(MSG_SYSCALL_ERR_MEM, env_error, 1));
	i = -1;
	index = ft_itoa(++i);
	if (!index)
		return (NULL);
	try = ft_strjoin(filename_prefix, index);
	while (access(try, F_OK) > -1)
	{
		free(try);
		index = ft_itoa(++i);
		try = ft_strjoin(filename_prefix, index);
		free(index);
	}
	free(filename_prefix);
	return (try);
}

static int	get_next_line_heredoc(char *stop, int fd)
{
	char	*line;
	int		len_limiter;

	len_limiter = ft_strlen(stop);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			exit(0);
		if (ft_strcmp(line, stop) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
	return (EXIT_SUCCESS);
}

static int	launch_heredoc(char *path_tmp, t_token *infile)
{
	char	*filename;
	char	*stop;
	int		fd;

	filename = NULL;
	fd = open(path_tmp, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		free(filename);
		return (EXIT_FAILURE);
	}
	stop = ft_substr(infile->start, 0, infile->len);
	if (get_next_line_heredoc(stop, fd))
	{
		close(fd);
		free(filename);
		return (EXIT_FAILURE);
	}
	free(stop);
	infile->start = path_tmp;
	infile->len = ft_strlen(path_tmp);
	signal_handler(sig_loop);
	return (EXIT_SUCCESS);
}

int	heredoc(t_token *token)
{
	char		*filename;

	signal_handler(sig_heredoc);
	filename = create_tmp_filename();
	if (!filename)
		return (error_msg_return_int(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
	if (launch_heredoc(filename, token))
	{
		free(filename);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
