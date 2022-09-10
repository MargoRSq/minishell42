
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
	char			*name;
	char			**argv;
	t_file			*fns_in;
	t_file			*fns_out;
	t_count			counter;
	struct s_cmd	*next;
}	t_cmd;

void	cmdlst_add_back(t_cmd **lst, t_cmd *new);
void	cmdlst_clear(t_cmd **lst);
t_cmd	*cmdlst_last(t_cmd *lst);
t_cmd	*cmdlst_new(t_token *tokens);
void	cmdlst_print(t_cmd *lst);


t_count	count_entities(t_token *tokens);
t_cmd	*create_commands(t_token *tokens);