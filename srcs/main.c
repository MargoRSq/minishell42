#include "minishell.h"


typedef struct s_entity
{
	int					code;
	int					len;
	char				*start;
	struct s_entity			*next;

}	t_entity;

typedef struct s_global
{
	
}	t_global;


int main(int ac, char **av, char **envp)
{
	char *line;
	t_env *env;
	t_sh sh;

	if (ac !=1)
		return 1;

	env = parse_envp(envp);
	// envlst_print(env);

	init_shell(&sh, env);
	start_shell(&sh);
	// do_pwd(&sh)
	// set_sh_level(env, sh);
	// printf("%s\n", get_env_value("SHLVL", env));
	// start_shell(&env, &sh, envp);
	// clear();

	// printf("%s\n", getenv("PWD"));

	return (1);
	// return (sh.status);

	// return (0);
}
