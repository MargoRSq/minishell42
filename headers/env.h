typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

t_env	*envlst_new(char *key, char *value);
t_env	*envlst_last(t_env *lst);
void	envlst_add_back(t_env **lst, t_env *new_lst);
void	envlst_clear(t_env **lst);
void	envlst_print(t_env *lst);

t_env	*parse_envp(char **envp);
char	*get_env_value(char *key, t_env *env);
t_env	*append_env_var(char *key, char *value);
t_env	*update_env_value(char *key, char *value);