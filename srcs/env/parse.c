#include "minishell.h"

static inline int	find_equals_sign(char *str)
{
	int	j;
	int	eq;

	j = -1;
	while (str[++j])
		if (str[j] == '=')
			return (j);
	return (-1);
}

t_env	*parse_envp(char **envp)
{
	t_env	*env;
	int		i;
	int		eq;
	char	*key;
	char	*value;

	env = NULL;
	i = -1;
	eq = 0;
	while (envp[++i])
	{
		eq = find_equals_sign(envp[i]);
		key = ft_substr(envp[i], 0, eq);
		value = ft_substr(envp[i], eq + 1, ft_strlen(envp[i]));
		envlst_add_back(&env, envlst_new(key, value));
	}
	return (env);
}
