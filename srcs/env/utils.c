#include "minishell.h"

char	*get_env_value(char *key, t_list *envlst)
{
	t_env	*tmp;

	while (envlst)
	{
		tmp = (t_env *)(envlst->content);
		if (!ft_strcmp(key, tmp->key))
			return (tmp->value);
		envlst = envlst->next;
	}
	return (NULL);
}
