#include "mi"

typedef struct s_fd
{
	int		fd1[2];
	int		fd2[2];
}	t_fd;

typedef struct s_file
{
	char			*name;
	t_token_type	type;
}	t_file;

typedef struct s_count
{
    short   in;
    short   out;
    short   words;
}   t_count;

typedef struct s_cmd
{
	char			**argv;
	t_file			*infile;
	t_file			*outfile;
	t_count			counter;
}	t_cmd;


t_cmd	*cmdlst_new(t_list *tokens);

t_count	count_entities(t_list *tokens);
t_list	*create_commands(t_list *tokens);
void	execute(t_env **env, t_list *cmd);
void	only_parent_process(t_env **env, t_cmd *cmd);
int		check_builtin(char *cmd);
char	*get_cmd(t_env *env, char *cmd);
void	multi_pipe_process(t_env **env, t_list *cmd);
int		try_builtin(t_cmd *cmds, t_env **env);
void	exec_first_cmd(t_env *env, t_cmd *cmd, t_fd *fds);
void	exec_middle_cmd(t_env *env, t_cmd *cmd, t_fd *fds);
void	exec_last_cmd(t_env *env, t_cmd *cmd, t_fd *fds);

void	execute(t_list **envlst, t_list *cmd);
void	only_parent_process(t_list **envlst, t_cmd *cmd);
void	multi_pipe_process(t_list **envlst, t_cmd *cmd);
int		try_builtin(t_cmd *cmds, t_list **envlst);
void	exec_first_cmd(t_list *envlst, t_cmd *cmd);
void	exec_middle_cmd(t_list *envlst, t_cmd *cmd);
void	exec_last_cmd(t_list *envlst, t_cmd *cmd);
