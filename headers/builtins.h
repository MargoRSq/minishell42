#include "minishell.h"

void 	execute_echo(char **cmd_argv);
void	execute_env(t_list *envlst, char **cmd_argv);
void 	execute_pwd(t_list *envlst);
void 	execute_unset(t_list **envlst, char **cmd_argv);
void 	execute_cd(t_list *envlst, char **cmd_argv);
void 	execute_exit(char **cmd_argv);
void	execute_export(t_list *envlst, char **cmd_argv);

int 	check_valid_env_key(char *str);
int 	check_valid_env_value(char *str);
void	change_or_append(t_list *envlst, char *new_key, char *new_value);
void	append_key(t_list *envlst, char *new_key);
void	free_arr(char **arr);

void 	clean_tokens_cmds(t_list *cmdlst, t_list *tokenlst);