typedef struct s_cmd
{
	char			*name;
	char			**argv;
	char			**fns_in;
	char			**fns_out;
	struct s_cmd	*next;
}	t_cmd;

void	cmdlst_add_back(t_cmd **lst, t_cmd *new);
void	cmdlst_clear(t_cmd **lst);
t_cmd	*cmdlst_last(t_cmd *lst);
t_cmd	*cmdlst_new(char *start, int len, int code);

typedef struct s_count
{
    short   in;
    short   out;
    short   words;
}   t_count;

t_count	count_entities(t_token *tokens);
t_cmd	*create_commands(t_token *tokens);