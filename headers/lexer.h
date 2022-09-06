#include "minishell.h"

typedef struct s_token
{
	char			*start;
	int				len;
	enum 			e_tokens code;
	struct			s_token *next;
}	t_token;

t_token		*tokenlst_last(t_token *lst);
t_token		*tokenlst_new(char *start, int len, int code);
void		tokenlst_add_back(t_token **lst, t_token *new_lst);
void		tokenlst_clear(t_token **lst);
void		tokenlst_print(t_token *lst);

int			find_end(char *ptr);
t_token		*lex_line(char *line);
