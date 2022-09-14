#include "minishell.h"

int count_arg(char **arg)
{
	int i;
	
	i = 0;
	while(arg[i] != NULL)
		i++;
	return(i);
}

void execute_exit(t_env *env, char **cmd_argv)
{
	int i;
	int len_arr;

	i = 0;
	len_arr = count_arg(cmd_argv);
	printf("exit\n");
	if(len_arr == 0)
		error_msg_return_minus("", 0, 1);
	else if (len_arr > 0)
	{
		while(ft_isdigit(cmd_argv[0][i]))
			i++;
		if ((size_t)i != ft_strlen(cmd_argv[0]))
			error_msg_return_minus(MSG_ERR_EXIT_NUM, 255, 1);
		else if (len_arr == 1)
			error_msg_return_minus("", ft_atoi(cmd_argv[0]) % 256, 1);
		else if (len_arr > 0)
			error_msg_return_minus(MSG_ERR_EXIT_ARGS, 1, 0);
	}
}