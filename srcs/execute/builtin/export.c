/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:08:05 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/19 19:10:08 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **sort_arr(char **arr, int size)
{
	int i;
	int j;
	char *tmp;
	
	i = 0;
	while(i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if(ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return(arr);
}

void print_arr_prefix(char **arr, int size)
{
	int i;

	i = 0;
	while(i < size)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, arr[i], ft_strlen(arr[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void print_sorted_env(t_env *env)
{
	char **arr;
	int size;

	int i;
	i = 0;
	size = envlst_size(env);
	arr = envlst_to_arr(env);
	arr = sort_arr(arr, size);
	print_arr_prefix(arr, size);
	// free_arr(arr);
}

int	equal_sign(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void check_key_exists(t_env *env, char *argv)
{
	char **key_value;
	char *exists;

	key_value = ft_split(argv, '=');
	exists = get_env_value(key_value[0], env);
	if (exists)
		envlst_delete_elem(key_value[0], &env);
	// free key_value
}

void do_export_argv(t_env *env, char **cmd_argv)
{
	int i;
	char **key_value;

	i = 0;
	while(cmd_argv[i])
	{
		printf("cmd_argv[%d] %s\n", i, cmd_argv[i]);
		
		if(!equal_sign(cmd_argv[i]))
		{
			if(!check_valid_env_key(cmd_argv[i]))
			{
				write(STDERR_FILENO, "minishell: export: `", 20);
				write(STDERR_FILENO, cmd_argv[i], ft_strlen(cmd_argv[i]));
				write(STDERR_FILENO, "': not a valid identifier\n", 27);
			}
			else 
				printf("exit with 0\n"); // 
		}
		else 
		{
			key_value = ft_split(cmd_argv[i], '=');
			if(!check_valid_env_key(key_value[0]) || (key_value[1] && !check_valid_env_value(key_value[1])))
			{
				write(STDERR_FILENO, "minishell: export: `", 20);
				write(STDERR_FILENO, cmd_argv[i], ft_strlen(cmd_argv[i]));
				write(STDERR_FILENO, "': not a valid identifier\n", 27);
			}
			else
			{
				//exit status 0
				check_key_exists(env, cmd_argv[i]);
				append_env_var(env, cmd_argv[i]);
			}
		}
		i++;
	}
	
}

void execute_export(t_env *env, char **cmd_argv)
{
	if(!cmd_argv[0]) 
		print_sorted_env(env);
	else
		do_export_argv(env, cmd_argv);
}