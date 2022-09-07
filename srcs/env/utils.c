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
	return (trigger_env_error());
}

t_env	*update_env_value(char *key, char *value)
{
	return (NULL);
}

t_env	*append_env_var(char *key, char *value)
{
	return (NULL);
}