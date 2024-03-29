/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptoshiko <ptoshiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:47:35 by ptoshiko          #+#    #+#             */
/*   Updated: 2022/10/13 17:18:09 by ptoshiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_fd
{
	int		fd1[2];
	int		fd2[2];
	int		in_fd;
	int		out_fd;
	int		in_tmp;
	int		out_tmp;
}	t_fd;

typedef struct s_file
{
	char			*name;
	t_token_type	type;
}	t_file;

typedef struct s_count
{
	short	in;
	short	out;
	short	words;
}	t_count;

typedef struct s_cmd
{
	char			**argv;
	t_file			*infile;
	t_file			*outfile;
	t_count			counter;
}	t_cmd;

typedef struct s_run
{
	t_list	*envlst;
	t_cmd	*cmd;
	t_fd	*fds;
	int		flag;
}	t_run;

t_cmd	*cmdlst_new(t_list *tokens);

t_count	count_entities(t_list *tokens);
t_list	*create_commands(t_list *tokens);
void	execute(t_list **envlst, t_list *cmdlst);
void	only_parent_process(t_list **envlst, t_list *cmdlst, t_fd *fds);
int		check_builtin(char *cmd);
char	*get_cmd(t_list *envlst, char *cmd);
void	multi_pipe_process(t_list **envlst, t_list *cmd, t_fd *fds);
int		try_builtin(t_cmd *cmds, t_list **env);
void	bin_run_multi(t_list *envlst, t_cmd *cmd, t_fd *fds, int fl);
void	exec_first_cmd(t_list *envlst, t_cmd *cmd, t_fd *fds);
void	exec_middle_cmd(t_list *envlst, t_cmd *cmd, t_fd *fds, int fl);
void	exec_last_cmd(t_list *envlst, t_cmd *cmd, t_fd *fds, int fl);
void	replace_fds_start(t_cmd *cmd, t_fd *fds);
void	replace_fds_finish(t_cmd *cmd, t_fd *fds);

#endif