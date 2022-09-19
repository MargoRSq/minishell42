/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:22:49 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/18 18:28:46 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*arr1;
	unsigned char	*arr2;
	int				i;

	arr1 = (unsigned char *)s1;
	arr2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (n != 0)
	{
		if (arr1[i] != arr2[i])
			return (arr1[i] - arr2[i]);
		if (arr1[i] == '\0' || arr2[i] == '\0')
			return (0);
		i++;
		n--;
	}
	return (0);
}

void execute_echo(char **cmd_argv)
{
	int i;
	int flag;

	i = 0;
	flag = 0;

	if (!cmd_argv[0])
	{
		printf("\n");
		return ;
	}
	while (cmd_argv[i] && !ft_strcmp(cmd_argv[i], "-n"))
	{
		flag = 1;
		i++;
	}
	while (cmd_argv[i])
	{
		printf("%s", cmd_argv[i]);
		if (cmd_argv[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 0)
		printf("\n");
}


