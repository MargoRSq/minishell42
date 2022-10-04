/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:08:05 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/04 19:16:51 by svyatoslav       ###   ########.fr       */
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

void	print_sorted_env(t_list *envlst)
{
	char	**arr;
	int		size;
	int		i;

	i = 0;
	size = ft_lstsize(envlst);
	arr = envlst_to_arr(envlst);
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

void	do_export_argv(t_list *envlst, char **cmd_argv)
{
	int		i;
	char	**key_value;

	i = 1;
	while (cmd_argv[i])
	{
		if (!equal_sign(cmd_argv[i]))
		{
			if (!check_valid_env_key(cmd_argv[i]))
				error_msg_return_void(MSG_ERR_EXPORT_KEY, cmd_argv[i], key_error, 0);
			else
				return; // exit code(0);
		}
		else
		{
			key_value = ft_split(cmd_argv[i], '='); // leaks
			if (!check_valid_env_key(key_value[0]) || (key_value[1] && !check_valid_env_value(key_value[1])))
				error_msg_return_void(MSG_ERR_EXPORT_KEY, cmd_argv[i], key_error, 0);
			else
				change_or_append(envlst, key_value[0], key_value[1]);
		}
		i++;
	}
}

void	execute_export(t_list *envlst, char **cmd_argv)
{
	if (!cmd_argv[1])
		print_sorted_env(envlst);
	else
		do_export_argv(envlst, cmd_argv);
}
