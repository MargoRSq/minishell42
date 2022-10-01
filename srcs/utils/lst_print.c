#include "minishell.h"

void	print_tokens(void *vtokens)
{
	t_token	*token;

	token = (t_token *)vtokens;
	printf("{text=%s, code=%d, len=%d} ",
		 ft_substr(token->start, 0, token->len),
		 token->code, token->len);
}

void	print_cmds(void *vcmds)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd;
	printf("{cmd=%s} ", cmd->argv);
}

void	print_env(void *venv)
{
	t_env	*env;

	env = (t_env *)(venv);
	if (ft_strcmp (env->value, ""))
		printf("%s=%s\n", env->key, env->value);
}

// // void	prin

// void	envlst_print(t_list *envlst)
// {
// 	t_env	*tmp;

// 	tmp = (t_env *)(envlst->content);
// 	if (!tmp)
// 		return ;
// 	while (envlst != NULL)
// 	{
// 		if (ft_strcmp (tmp->value, ""))
// 		{
// 			printf("%s=%s\n", tmp->key, tmp->value);
// 			envlst = envlst->next;
// 			if (envlst == NULL)
// 				return ;
// 		}
// 	}
// }