/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:49:15 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 18:10:02 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_with_message(void)
{
	if (g_status.exit_msg)
		printf("%s", g_status.exit_msg);
	else
		printf("Goodbye!\n");
	return (g_status.exit_code);
}

static void	init_status(void)
{
	g_status.exit_code = 0;
	g_status.exit_msg = NULL;
	g_status.interrupt = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_list	*envlst;

	(void)av;
	if (ac != 1)
		return (1);
	init_status();
	envlst = parse_envp(envp);
	init_shell(envlst);
	start_shell(&envlst);
	return (exit_with_message());
}
