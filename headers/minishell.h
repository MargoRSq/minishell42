#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>

#include "libft.h"
#include "../libs/libreadline/include/readline/readline.h"
#include "../libs/libreadline/include/readline/history.h"

#include "enums.h"
#include "env.h"
#include "lexer.h"
#include "errors.h"
#include "utils.h"
#include "builtins.h"
#include "cmd.h"
#include "get_next_line.h"


typedef struct s_status
{
	int			exit_code;
	char		*exit_msg;
	short		interrupt;
	short		shell_level;
	short		rl_fd;
}	t_status;

t_status g_status;

void	init_shell(t_list *envlst);
void	start_shell(t_list **envlst);

#endif
