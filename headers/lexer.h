#include "minishell.h"

typedef struct s_tmp_token
{
	char	*str;
	int		len;
	int		tmp_code;
	short	type;
}	t_tmp;

typedef struct s_cpy
{
	char	*dst;
	char	*src;
	int		*ir;
	int		*jr;
	int		is_dq;
	short	tp;
}	t_cpy;

typedef struct s_len
{
	int	len;
	int	final_len;
}	t_len;

typedef struct s_token
{
	char			*start;
	int				len;
	// short			after_sep;
	t_token_type	code;
	// struct			s_token *next;
}	t_token;

t_token		*tokenlst_last(t_token *lst);
t_token		*tokenlst_new(char *start, int len, int code);
void		tokenlst_add_back(t_token **lst, t_token *new_lst);
void		tokenlst_clear(t_token **lst);
void		tokenlst_print(t_token *lst);

int			find_end(char *ptr);
t_list		*lex_line(char *line, t_env *env);

char		*unpack(char *str, t_len lens, short is_dq, t_env *env);
t_token		*unpack_tmp_token(t_tmp tkn, t_env *env);
t_tmp		create_tmp_token(int len, int code, char *line);
char		*fetch_envstr(char *str, int pos, t_env *env);
int			ft_envcpy(char *start, int pos, char *new_start, t_env *env);

int	get_code(int sy, int len);
int	get_skip_distance(char *sy, int len);

int 	counter_str_single_quote(char *str);
int counter_skip_unpacked_env(char *str, t_env *env);
int	skipper_str_single_quote(char *str, int *iptr, short is_dq);
int	skipper_str_with_env(char *str, int *iptr, int len, t_env *env);
int			count_final_len(char *str, int len, short is_dq, t_env *env);

void	check_tokens(t_list *token, t_env *env);
int		heredoc(t_token *token, t_env *env);
void	signal_handler_heredoc(void);