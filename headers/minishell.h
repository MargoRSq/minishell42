#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

# define CYAN "\e[46m"


/*
	environment
*/
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

t_env	*envlst_new(char *key, char *value);
t_env	*envlst_last(t_env *lst);
void	envlst_add_back(t_env **lst, t_env *new);
void	envlst_clear(t_env **lst);
void	envlst_print(t_env *lst);
t_env	*parse_envp(char **envp);


#endif