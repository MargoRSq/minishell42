#include "minishell.h"

static int	exit_with_message()
{
	if (g_status.exit_msg)
		printf("%s", g_status.exit_msg);
	else
		printf("Goodbye!\n");
	return (g_status.exit_code);
}

static void	init_status()
{
	g_status.exit_code = 0;
	g_status.exit_msg = NULL;
	g_status.interrupt = 0;
}

int main(int ac, char **av, char **envp)
{
	char *line;
	t_env *env;

	if (ac != 1)
		return 1;

	init_status();
	env = parse_envp(envp);
	envlst_print(env);

	init_shell(env);
	start_shell(env);

	return (exit_with_message());
}
