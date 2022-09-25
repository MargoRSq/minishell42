/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:08:05 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/25 20:49:28 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sort_arr(char **arr, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(arr[j], arr[j + 1]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

void	print_arr_prefix(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, arr[i], ft_strlen(arr[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	print_sorted_env(t_env *env)
{
	char	**arr;
	int		size;
	int		i;

	i = 0;
	size = envlst_size(env);
	arr = envlst_to_arr(env);
	arr = sort_arr(arr, size);
	print_arr_prefix(arr, size);
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

void	remove_if_exists(t_env *env, char *argv)
{
	char	**key_value;
	t_env	*tmp;

	key_value = ft_split(argv, '=');
	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(key_value[0], tmp->key))
		{
			envlst_delete_elem(key_value[0], &env);
			return ;
		}
		tmp = tmp->next;
	}
}

void	do_export_argv(t_env *env, char **cmd_argv)
{
	int		i;
	char	**key_value;

	i = 0;
	while (cmd_argv[i])
	{
		if (!equal_sign(cmd_argv[i]))
		{
			if (!check_valid_env_key(cmd_argv[i]))
				error_msg_return_void(MSG_ERR_EXPORT_KEY, cmd_argv[i], 1, 0);
			else
				return ; // exit code (0);
		}
		else
		{
			key_value = ft_split(cmd_argv[i], '=');
			if (!check_valid_env_key(key_value[0]) || (key_value[1] && !check_valid_env_value(key_value[1])))
				error_msg_return_void(MSG_ERR_EXPORT_KEY, cmd_argv[i], 1, 0);
			else
			{
				remove_if_exists(env, cmd_argv[i]);
				append_env_var(env, cmd_argv[i]);
			}
		}
		i++;
	}
}

void	execute_export(t_env *env, char **cmd_argv)
{
	if (!cmd_argv[0]) 
		print_sorted_env(env);
	else
		do_export_argv(env, cmd_argv);
}
