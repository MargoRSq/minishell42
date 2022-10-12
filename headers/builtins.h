/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:36:41 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/12 18:46:42 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

void	execute_echo(char **cmd_argv);
void	execute_env(t_list *envlst, char **cmd_argv);
void	execute_pwd(void);
void	execute_unset(t_list **envlst, char **cmd_argv);
void	execute_cd(t_list *envlst, char **cmd_argv);
void	execute_exit(char **cmd_argv);
void	execute_export(t_list *envlst, char **cmd_argv);

int		check_valid_env_key(char *str);
int		check_valid_env_value(char *str);
void	change_or_append(t_list *envlst, char *new_key, char *new_value);
void	append_key(t_list *envlst, char *new_key);
void	free_arr(char **arr);

void	clean_arr(char **arr);
void	print_arr_prefix(char **arr, int size);
void	print_sorted_env(t_list *envlst);
int		equal_sign(char *token);

void	clean_tokens_cmds(t_list *cmdlst, t_list *tokenlst);

#endif