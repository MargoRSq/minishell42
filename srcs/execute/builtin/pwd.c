/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svyatoslav <svyatoslav@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:28:23 by angelinamaz       #+#    #+#             */
/*   Updated: 2022/10/04 19:24:45 by svyatoslav       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(t_list *envlst)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_msg_return_void(MSG_SYSCALL_ERR_GETCWD, NULL,
				cwd_error, 1));
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
}
