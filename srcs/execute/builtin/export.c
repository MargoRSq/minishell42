/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 13:08:05 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/09 21:04:42 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**form_key_value(char *arg)
{
	char	**key_value;
	int		i;
	int		count;
	int		len_arg;

	i = 0;
	count = 0;
	if (!arg)
		return (NULL);
	len_arg = ft_strlen(arg);
	key_value = (char **)malloc(sizeof(char *) * (2 + 1));
	if (!key_value)
		return (NULL);
	key_value[2] = NULL;
	while (arg[i] != '=' && arg[i])
	{
		i++;
		count++;
	}
	key_value[0] = ft_substr((const char *) arg, 0, count);
	key_value[1] = ft_substr((const char *) arg, count + 1, len_arg - count);
	return (key_value);
}

void	add_key_value(char *argv, char	**key_value, t_list *envlst)
{
	if (!check_valid_env_key(key_value[0]) || (key_value[1] && \
				!check_valid_env_value(key_value[1])))
	{
		clean_arr(key_value);
		return (error_msg_return_void(MSG_ERR_EXPORT_KEY, argv,
				key_error, 0));
	}
	else
	{
		change_or_append(envlst, key_value[0], key_value[1]);
		free(key_value);
	}
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
				return (error_msg_return_void(MSG_ERR_EXPORT_KEY, cmd_argv[i],
						key_error, 0));
			else
				append_key(envlst, ft_strdup(cmd_argv[i]));
		}
		else
		{
			key_value = form_key_value(cmd_argv[i]);
			add_key_value(cmd_argv[i], key_value, envlst);
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
