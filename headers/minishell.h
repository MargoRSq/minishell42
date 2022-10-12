/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:51:38 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/12 19:14:40 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <sys/types.h>
// #include <wait.h>
# include <sys/stat.h>
# include <fcntl.h>
// #include <signal.h>
# include <termios.h>

# include "enums.h"
# include "env.h"
# include "lexer.h"
# include "errors.h"
# include "utils.h"
# include "builtins.h"
# include "cmd.h"
# include "get_next_line.h"

typedef struct s_status
{
	int			exit_code;
	char		*exit_msg;
	short		interrupt;
	short		shell_level;
	short		rl_fd;
}	t_status;

t_status	g_status;

void	start_shell(t_list **envlst);

#endif
