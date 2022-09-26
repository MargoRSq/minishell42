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

char		*trigger_home_error()
{
	g_status.interrupt = 1;
	g_status.exit_msg = MSG_ERR_HOME;
	g_status.exit_code = home_error;
	return(NULL);
}

int 	trigger_pwd_error()
{
	g_status.interrupt = 1;
	g_status.exit_msg = MSG_ERR_PWD;
	g_status.exit_code = pwd_error;
	return(-1);
}

int trigger_exit_error()
{
	g_status.interrupt = 1;
	g_status.exit_msg = MSG_ERR_EXIT_NUM;
	g_status.exit_code = 1;
	return(-1);
}

// int error_msg_return_minus(char *msg, int code)
// {
// 	g_status.interrupt = 1;
// 	g_status.exit_msg = msg;
// 	g_status.exit_code = code;
// 	return(-1);
// }

int error_msg_return_minus(char *msg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	g_status.exit_msg = msg;
	g_status.exit_code = code;
	return(-1);
}

void	error_msg_return_void(char *msg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	g_status.exit_msg = msg;
	g_status.exit_code = code;
}

char	*error_msg_return_charz(char *msg, int code, short interrupt)
{
	g_status.interrupt = interrupt;
	g_status.exit_msg = msg;
	g_status.exit_code = code;
	return (NULL);
}

// int 	trigger_сd_error()
// {
// 	g_status.interrupt = 1;
// 	g_status.exit_msg = MSG_ERR_CD;
// 	g_status.exit_code = pwd_error;
// 	return(-1);
// }
