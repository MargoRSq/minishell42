#include "minishell.h"

// int	cmd_len(t_cmd *cmd)
// {
// 	t_cmd	*tmp;
// 	int		len;

// 	len = 0;
// 	tmp = cmd;
// 	while (tmp)
// 	{
// 		len++;
// 		tmp = tmp->next;
// 	}
// 	return len;
// }

//int	**make_pipe_space(int **pipes, int len)
//{
//	int i;
//
//	pipes = malloc(sizeof(int *) * (len - 1));
//	if (!pipes)
//		return (error_msg_return_int(MSG_ERR_MEM, NULL, malloc_error,
//											1));
////		trigger_malloc_error();//need to clarify!
//	i = 0;
//	while (i < (len - 1))
//	{
//		pipes[i] = malloc(sizeof(int) * 2);
//		if (!pipes[i])
//			return (error_msg_return_int(MSG_ERR_MEM, NULL, malloc_error,
//										 1));
//		i++;
//	}
//	return (pipes);
//}

void	begin_pipes(t_cmd *cmd, int len)
{
	t_cmd	*tmp;

	tmp = cmd;
//	while(tmp)
//	{
//		tmp = tmp->next
//	}
}

void	multi_pipe_process(t_env **env, t_cmd *cmd)
{
//	int		len;
//	int 	**pipes;
//	int		i;
	t_cmd	*tmp;
	t_cmd	*prev;
	int		fd1[2];
	int		fd_tmp;

//	len = ft_lstsize((t_list *)cmd);
//	pipes = NULL;
//	pipes = make_pipe_space(pipes, len);
//	begin_pipes(cmd, len);
	tmp = cmd;
	prev = NULL;
	while(tmp != NULL)
	{
		if (pipe(fd1) == -1)
			error_msg_return_void(MSG_SYSTEM_ERR_PIPE, NULL, pipe_error, 1);
		if (prev == NULL)
			exec_first_cmd(*env, tmp, fd1);
		else if (((t_list *)tmp)->next == NULL)
			exec_last_cmd(*env, tmp);
		else
			exec_middle_cmd(*env, tmp);
		prev = tmp;
		tmp = (t_cmd *)((t_list *)tmp)->next;
	}
}