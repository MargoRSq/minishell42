#include "minishell.h"

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

t_list	*parse_envp(char **envp);

t_env	*envlst_new(char *key, char *value);

void	envlst_print(t_list *envlst);
void	envlst_delete_elem(void *content);
void	envlst_delete_one(char *key, t_list **envlst);

char	**envlst_to_arr(t_list *envlst);
char	*get_env_value(char *key, t_list *envlst);