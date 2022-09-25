/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:19:12 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/09/25 21:07:16 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int error_msg_minus(char *msg, char *arg, int code, short interrupt)
// {
// 	g_status.interrupt = interrupt;
// 	g_status.exit_msg = msg;
// 	g_status.exit_code = code;
// 	return(-1);
// }

void	error_msg_return_void(char *msg, char *arg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	printf(msg, arg);
	g_status.exit_code = code;
}

// //slava
// char *error_msg_return_charz(char *msg, int code, short interrupt)
// {
	
// }

void	*trigger_malloc_error()
{
	g_status.interrupt = 1;
	g_status.exit_code = malloc_error;
	g_status.exit_msg = MSG_ERR_MEM;
	return (NULL);
}


int		trigger_unclosed_quote_error(char q_type)
{
	g_status.interrupt = 1;
	if ((int)q_type == s_quote)
		g_status.exit_msg = MSG_ERR_CMD_USQ;
	else
		g_status.exit_msg = MSG_ERR_CMD_UDQ;
	g_status.exit_code = unclosed_quote_error;
	return (-1);
}


int		trigger_too_many_redirects_error()
{
	g_status.interrupt = 1;
	g_status.exit_msg = MSG_ERR_CMD_TMR;
	g_status.exit_code = unclosed_quote_error;
	return (-1);
}





