/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:19:12 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/12 14:29:10 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *msg, char *arg)
{
	int	stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf(msg, arg);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
}

void	error_msg_return_void(char *msg, char *arg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	print_error(msg, arg);
	g_status.exit_code = code;
}

int	error_msg_return_int(char *msg, char *arg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	print_error(msg, arg);
	g_status.exit_code = code;
	return (-1);
}

void	*error_msg_return_null(char *msg, char *arg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	print_error(msg, arg);
	g_status.exit_code = code;
	return (NULL);
}

char	*error_msg_return_charz(char *msg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	g_status.exit_msg = msg;
	g_status.exit_code = code;
	return (NULL);
}
