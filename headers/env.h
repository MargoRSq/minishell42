/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:49:59 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 18:50:33 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env
{
	char				*key;
	char				*value;
}	t_env;

t_list	*parse_envp(char **envp);

t_env	*envlst_new(char *key, char *value);

void	envlst_print(t_list *envlst);
void	envlst_delete_elem(void *content);
void	envlst_delete_one(char *key, t_list **envlst);

char	**envlst_to_arr(t_list *envlst);
char	*get_env_value(char *key, t_list *envlst);

#endif