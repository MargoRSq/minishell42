#include "minishell.h"

char	*get_env_value(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void append_env_var(t_env *env, char *arg)
{
	char		**key_value;
	t_env 		*new_elem;

	key_value = ft_split(arg, '=');
	if (!key_value)
		printf("malloc error"); //
	if(!key_value[1])
		key_value[1] = ft_strdup("");
	new_elem = envlst_new(key_value[0], key_value[1]);
	if (!new_elem)
		printf("malloc error"); // 
	envlst_add_back(&env, new_elem);
	// free key_value;
}

