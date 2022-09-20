/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:22:05 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/19 16:08:27 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int check_valid(char *str)
// {
// 	if (!ft_isalpha(*str) && *str != '_')
// 		return (1);
// 	str++;
// 	while (*str != '\0')
// 	{
// 		if (!ft_isalnum(*str) && *str != '_')
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

void execute_unset(t_env *env, char **cmd_argv)
{
	int  i;

	i = 0;
	while(cmd_argv[i])
	{
		if(!check_valid_env_key(cmd_argv[i]))
		{
			write(STDERR_FILENO, "minishell: unset: `", 19);
			write(STDERR_FILENO, cmd_argv[i], ft_strlen(cmd_argv[i]));
			write(STDERR_FILENO, "': not a valid identifier\n", 27);
		}
		envlst_delete_elem(cmd_argv[i], &env);
		i++;
	}
}
