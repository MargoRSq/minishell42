#ifndef ERROR_MSGS_H
# define ERROR_MSGS_H

int		trigger_unclosed_quote_error(char q_type); // dasdasd

void	error_msg_return_void(char *msg, char *arg, int code, short interrupt);
void	*error_msg_return_null(char *msg, char *arg, int code, short interrupt);
char	*error_msg_return_charz(char *msg, int code, short interrupt);
int		error_msg_return_int(char *msg, char *arg, int code, short interrupt);

# define MSG_SYSCALL_ERR_GETCWD "minishell: getcwd failed\n"
# define MSG_SYSCALL_ERR_CHDIR	"minishell: %s: chdir failed\n"
# define MSG_SYSCALL_ERR_MEM 	"minishell: Memory allocation failed\n"
# define MSG_ERR_CD_OLDPWD		"minishell: cd: OLDPWD not set\n"
# define MSG_ERR_HOME			"minishell: cd: HOME not set\n"
# define MSG_ERR_ENV			"minishell: ENV error .\n"
# define MSG_ERR_ENV_ARGS		"minishell: %s: No such file or directory\n"
# define MSG_ERR_EXIT_NUM\
	"minishell: exit: %s: Numeric argument required\n"
# define MSG_ERR_EXIT_ARGS		"minishell: exit: Too many arguments\n"
# define MSG_ERR_EXPORT_KEY\
	"minishell: export: `%s': not a valid identifier\n"
# define MSG_ERR_UNSET_KEY\
	"minishell: unset: `%s': not a valid identifier\n"
# define MSG_ERR_RL_FD\
	"minishell: unset: `%s': Readline file error\n"

# define MSG_ERR_EXECVE			"minishell: EXECVE error .\n"
# define MSG_ERR_CMD_TMR		"minishell: parse error\n"
# define MSG_ERR_CMD_USQ\
	"minishell: Syntax error: command has unclosed \' sign\n"
# define MSG_ERR_CMD_UDQ\
	"minishell: Syntax error: command has unclosed \" sign\n"
# define MSG_ERR_PIPE_LOC\
	"minishell: parse error: pipe at the start or at the end\n"
# define MSG_ERR_REDIR_PARSE\
	"minishell: parse error: wrong redir usage\n"
# define MSG_ERR_FILE_NEXISTS\
	"minishell: parse error: file not exists\n"
# define MSG_ERR_PIPE			"minishell: Pipes creation fail\n"
#endif