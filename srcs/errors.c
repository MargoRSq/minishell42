/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:19:12 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 18:32:45 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg_return_void(char *msg, char *arg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	printf(msg, arg);
	g_status.exit_code = code;
}

int	error_msg_return_int(char *msg, char *arg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	printf(msg, arg);
	g_status.exit_code = code;
	return (-1);
}

void	*error_msg_return_null(char *msg, char *arg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	printf(msg, arg);
	g_status.exit_code = code;
	return (NULL);
}

int	trigger_unclosed_quote_error(char q_type)
{
	g_status.interrupt = 1;
	if ((int)q_type == s_quote)
		g_status.exit_msg = MSG_ERR_CMD_USQ;
	else
		g_status.exit_msg = MSG_ERR_CMD_UDQ;
	g_status.exit_code = unclosed_quote_error;
	return (-1);
}

char	*error_msg_return_charz(char *msg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	g_status.exit_msg = msg;
	g_status.exit_code = code;
	return (NULL);
}
