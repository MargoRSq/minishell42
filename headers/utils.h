/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:52:17 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/10 18:52:55 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# define HISTORY_FILE		".minishell_history"
# define TMP_FILE_PREFIX	"/.minishell_heredoc_"

# define CYAN "\e[46m"
# define DEFAULT_PREFIX "\e[1;34mmaybach$ \e[0;37m\e[1;32m~"
# define DOLLAR "\e[1;34m$ \e[0;37m"

void	print_tokens(void *vtokens);
void	print_cmds(void *vcmds);
void	print_env(void *venv);

void	signal_handler(t_signal_type code);

#endif