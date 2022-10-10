/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 18:44:09 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 18:17:57 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(void *vtokens)
{
	t_token	*token;

	token = (t_token *)vtokens;
	printf("{text=%s, code=%d, len=%d} ",
		ft_substr(token->start, 0, token->len),
		token->code, token->len);
}

void	print_cmds(void *vcmds)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)vcmds;
	printf("{cmd=%s}\n", cmd->argv[0]);
}

void	print_env(void *venv)
{
	t_env	*env;

	env = (t_env *)(venv);
	if (env->value)
		printf("%s=%s\n", env->key, env->value);
}
