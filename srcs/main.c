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

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_list	*envlst;
	char	**arr;
	int		len;
	
	arr = ft_split("env ", ' ');

	if (ac != 1)
		return (1);
	init_status();
	envlst = parse_envp(envp);
	execute_env(envlst, arr);

	// all works 



	// ft_lstiter(env, print_env);
	// init_shell(envlst);
	// start_shell(&envlst);
	return (exit_with_message());
}
