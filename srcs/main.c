#include "minishell.h"


void	start_input_loop()
{

}

/*
	env info
*/

/*
	shell info
*/
typedef struct s_sh
{
	int					key;
	char				*value;
	t_env				*env;
}	t_sh;

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


	(void)ac; (void)av; (void)envp;

	if (ac !=1)
		return 1;

	env = parse_envp(envp);
	envlst_print(env);

	// int i = -1;
		// printf("%s\n", envp[i]);
	
	// env = parse_env(envp);
	// set_sh_level(env, sh)
	// start_shell(&env, &sh, envp);
	// clear();

	// printf("%s\n", getenv("PWD"));

	return (1);
	// return (sh.status);

	// while(1)
	// {
	// 	line = readline("\e[1;34mmaybach$ \e[0;37m");
	// 	printf("---%s---\n", line);
	// 	add_history(line);
	// }
	// return (0);
}
