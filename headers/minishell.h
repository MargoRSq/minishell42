#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

#include "enums.h"
#include "env.h"
#include "lexer.h"
#include "errors.h"
#include "utils.h"


typedef struct s_status
{
	int			exit_code;
	char		*exit_msg;
	short		interrupt;

}	t_status;

typedef struct s_sh
{
	int					level;
	int					exit_status;
	t_env				*env;
}	t_sh;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

t_status g_status;

void	init_shell(t_sh *sh, t_env *env);
void	start_shell(t_sh *sh);

#endif
