/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelinamazurova <angelinamazurova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:22:05 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/09/05 23:06:04 by angelinamaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static inline int check_valid(char *str)
// {
// 	if (!ft_isalpha(*str) && *str != '_')
// 		return (1);
// 	str++;
// 	while (*str != '\0')
// 	{
// 		if (!ft_isalnum(*str) && *str != '+' && *str != '*' && *str != '_')
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }

// void execute_unset(t_env *env, char **cmd_argv)
// {
// 	int  i;

// 	i = 0;
// 	while(cmd->args[i])
// 	{
// 		if(check_valid(cmd->args[i]));
// 		{
// 			write(STDERR_FILENO, "minishell: unset: `", 19);
// 			write(STDERR_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
// 			write(STDERR_FILENO, "': not a valid identifier\n", 27);
// 		}
// 		envlst_delete_elem(cmd->args[i], sh->env);
// 		i++;
	// }
// }
