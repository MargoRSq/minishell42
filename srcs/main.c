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

	// char **arr;
	// int len;
	// int i;

	if (ac != 1)
		return 1;
	init_status();
	env = parse_envp(envp);

	// i = 0;
	// len = envlst_size(env);
	// arr = envlst_to_arr(env);
	// while(i < len )
	// {
	// 	printf("%s\n", arr[i]);
	// 	i++;
	// }

	init_shell(env);
	start_shell(env);

	return (exit_with_message());
}
