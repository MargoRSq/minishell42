
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
	// char			*name;
	char			**argv;
	t_list			*fns_in;
	t_list			*fns_out;
	int				fd_in;
	int				fd_out;
	t_count			counter;
	// struct s_cmd	*next;
}	t_cmd;

void	cmdlst_add_back(t_cmd **lst, t_cmd *new);
void	cmdlst_clear(t_cmd **lst);
t_cmd	*cmdlst_last(t_cmd *lst);
t_cmd	*cmdlst_new(t_list *tokens);
void	cmdlst_print(t_cmd *lst);


t_count	count_entities(t_list *tokens);
t_list	*create_commands(t_list *tokens);
void	execute(t_list **envlst, t_list *cmd);
void	only_parent_process(t_list **envlst, t_cmd *cmd);
void	multi_pipe_process(t_list **envlst, t_cmd *cmd);
int		try_builtin(t_cmd *cmds, t_list **envlst);
void	exec_first_cmd(t_list *envlst, t_cmd *cmd);
void	exec_middle_cmd(t_list *envlst, t_cmd *cmd);
void	exec_last_cmd(t_list *envlst, t_cmd *cmd);
