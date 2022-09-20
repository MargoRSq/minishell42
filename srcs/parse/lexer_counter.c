#include "minishell.h"

int inline counter_skip_unpacked_env(char *str, t_env *env)
{
	int		i;
	int		len;
	char	*var_key;
	char	*var_value;

	i = -1;
	len = 0;
	while (str[++i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '$')
		len++;
	var_key = ft_substr(str, 0, len);
	var_value = get_env_value(var_key, env);
	// *(iptr) += ft_strlen(var_key);
		return (ft_strlen(var_value));	
	return (0);
}

int counter_str_single_quote(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (str[++i] != '\'')
		len++;
	return (len);
}

inline int	skipper_str_single_quote(char *str, int *iptr, short is_dq)
{
	int	tmp;
	int	result;

	result = 0;
	tmp = counter_str_single_quote(&str[*(iptr) + 1]) ;
	result += tmp;
	if (is_dq)
		result += 2;
	*iptr += tmp + 1;
	return (result);
}

inline int	skipper_str_with_env(char *str, int *iptr, int len, t_env *env)
{
	int	tmp;
	int	result;

	result = 0;
	tmp = counter_skip_unpacked_env(&str[*(iptr) + 1], env);
	result += tmp;
	(*iptr)++;
	while (*(iptr) < len && str[*(iptr)] != '\'' && str[*(iptr)] != '\"'
		&& str[*(iptr)] != ' ' && str[*(iptr)] != '$')
		(*iptr)++;
	return (result);
}

int count_final_len(char *str, int len, short is_dq, t_env *env)
{
	int	i;
	int	final_len;

	final_len = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] == '\'')
			final_len += skipper_str_single_quote(str, &i, is_dq);
		else if (str[i] == '$')
			final_len += skipper_str_with_env(str, &i, len, env);
		else
		{
			i++;
			final_len++;
		}
	}
	return (final_len);
}