#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

# define HISTORY_FILE	".minishell_history"

# define CYAN "\e[46m"
# define DEFAULT_PREFIX "\e[1;34mmaybach$ \e[0;37m\e[1;32m~"
# define DOLLAR "\e[1;34m$ \e[0;37m"


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
char	*get_env_value(char *key, t_env *env);
t_env	*append_env_var(char *key, char *value);
t_env	*update_env_value(char *key, char *value);

/*
	main shell parameters
*/
typedef struct s_sh
{
	int					level;
	int					exit_status;
	t_env				*env;
}	t_sh;

void	init_shell(t_sh *sh, t_env *env);
void	start_shell(t_sh *sh);

#endif