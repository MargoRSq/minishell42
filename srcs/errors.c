#include "minishell.h"

void	*trigger_malloc_error()
{
	g_status.interrupt = 1;
	g_status.exit_code = malloc_error;
	g_status.exit_msg = MSG_ERR_MEM;
	return (NULL);
}

void	*trigger_env_error()
{
	g_status.interrupt = 1;
	g_status.exit_code = env_error;
	g_status.exit_msg = MSG_ERR_ENV;
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