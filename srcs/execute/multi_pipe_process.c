#include "minishell.h"

void	multi_pipe_process(t_list **envlst, t_list *cmdlst)
{
	t_cmd	*tmp;
	t_cmd	*prev;
	t_fd	fds;
	int		i;

	prev = NULL;
	i = 0;
	while (cmdlst && ++i)
	{
		tmp = (t_cmd *)(cmdlst->content);
		if (prev == NULL)
			exec_first_cmd(*envlst, tmp, &fds);
		else if (cmdlst->next == NULL)
			exec_last_cmd(*envlst, tmp, &fds, i);
		else
			exec_middle_cmd(*envlst, tmp, &fds, i);
		prev = tmp;
		cmdlst = cmdlst->next;
	}
	while (wait(0) != -1)
		;
}