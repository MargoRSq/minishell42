#include "minishell.h"

void execute_echo(char **cmd_argv);
// void execute_echo(void);
void execute_env(t_env *env);
void execute_pwd(t_env *env);
void execute_unset(t_env *env, char **cmd_argv);
void execute_cd(t_env *env, char **cmd_argv);
void execute_exit(t_env *env, char **cmd_argv);

char *get_cur_dir(t_env *env);