#include "env.h"

typedef struct s_cmd
{
	char			*name;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

void execute_echo(char **cmd_argv);
void execute_env(t_env *env);
void execute_pwd(t_env *env);
void execute_unset(t_env *env, char **cmd_argv);
