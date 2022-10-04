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

	// int		i;
	// char	**arr;
	// int		len;
	
	if (ac != 1)
		return (1);

	// i = 0;
	// arr = ft_split("env ", ' ');

	init_status();
	envlst = parse_envp(envp);

	// len = ft_lstsize(envlst);
	// execute_env(envlst, arr);
	// ft_lstclear(&envlst, envlst_delete_elem);
	// while(arr[i])
	// {
	// 	free(arr[i]);
	// 	i++;
	// }
	// free(arr);
	// all works 
	// ft_lstiter(env, print_env);
	
	init_shell(envlst);
	start_shell(&envlst);
	return (exit_with_message());
}
