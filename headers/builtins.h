#include "minishell.h"

void 	execute_echo(char **cmd_argv);
void	execute_env(t_list *envlst, char **cmd_argv);
void 	execute_pwd(t_list *envlst);
void 	execute_unset(t_list **envlst, char **cmd_argv);
void 	execute_cd(t_list *envlst, char **cmd_argv);
void 	execute_exit(char **cmd_argv);
void	execute_export(t_list *envlst, char **cmd_argv);

char *get_cur_dir(t_list *envlst);
int check_valid_env_key(char *str);
int check_valid_env_value(char *str);
void	change_or_append(t_list *envlst, char *new_key, char *new_value);

void free_arr(char **arr);