#include "minishell.h"

typedef struct s_tmp_token
{
	char	*str;
	int		len;
	// int		tmp_code;
	short	type;
	short	sep;
}	t_tmp;

typedef struct s_token
{
	char			*start;
	int				len;
	short			after_sep;
	t_token_type	code;
	struct			s_token *next;
}	t_token;

t_token		*tokenlst_last(t_token *lst);
t_token		*tokenlst_new(char *start, int len, int code, int sep);
void		tokenlst_add_back(t_token **lst, t_token *new_lst);
void		tokenlst_clear(t_token **lst);
void		tokenlst_print(t_token *lst);

int			find_end(char *ptr);
t_token		*lex_line(char *line, t_env *env);
