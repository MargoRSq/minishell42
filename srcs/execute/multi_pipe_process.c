#include "minishell.h"

int	**make_pipe_space(int **pipes, int len)
{
	int i;

	pipes = malloc(sizeof(int *) * (len - 1));
	if (!pipes)
		return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL, 
			malloc_error, 1));
	i = 0;
	while (i < (len - 1))
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (error_msg_return_null(MSG_SYSCALL_ERR_MEM, NULL,
				malloc_error, 1));
		i++;
	}
	return (pipes);
}

void	begin_pipes(int **pipes, int len)
{
	int	i;

	i = 0;
	while(i < (len - 1))
	{
		if(pipe(pipes[i]))
//			trigger_pipes_error();//need to feat a new func
		i++;
	}
}

void	multi_pipe_process(t_list **envlst, t_cmd *cmd)
{
	int		len;
	int 	**pipes;
	int		i;
	t_cmd	*tmp;
	t_cmd	*prev;

	len = ft_lstsize((t_list *)cmd);
	pipes = NULL;
	pipes = make_pipe_space(pipes, len);
	begin_pipes(pipes, len);
	tmp = cmd;
	prev = NULL;
	while(tmp != NULL)
	{

		if (prev == NULL)
			exec_first_cmd(*envlst, tmp);
		else if (((t_list *)tmp)->next == NULL)
			exec_last_cmd(*envlst, tmp);
		else
			exec_middle_cmd(*envlst, tmp);
		prev = tmp;
		tmp = (t_cmd *)((t_list *)tmp)->next;
	}
}