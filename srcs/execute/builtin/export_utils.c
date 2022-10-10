/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:47:43 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 16:53:43 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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
	clean_arr(arr);
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
