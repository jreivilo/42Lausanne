/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:33:00 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/13 14:29:05 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_last_pipe(t_tree *tree)
{
	t_tree	*tmp;

	tmp = tree;
	while (tmp->father != NULL \
		&& tmp->father->token >= 4 && tmp->father->token <= 8)
		tmp = tmp->father;
	if (tree->father == NULL || tree->father->token != PIPE)
		return (1);
	return (0);
}

void	set_variable_pipe_exec(t_bash *bash, int *status)
{
	bash->hrdc = 0;
	bash->in_fd = 0;
	bash->out_fd = 1;
	*status = 0;
}

void	check_last_pipe_utils(t_bash *bash, int *wait, int *status)
{
	while (1)
	{
		*wait = waitpid(-1, &(*status), 0);
		if (*wait == bash->pid)
		{
			if (WIFSIGNALED(*status))
				g_status = 128 + WTERMSIG(*status);
			else if (WIFEXITED(*status))
				g_status = WEXITSTATUS(*status);
		}
		else if (*wait == -1)
			break ;
	}
}

int	signals_pipe_exec_utils(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
		{
			printf("Quit : %d\n", status);
			return (ERROR);
		}
		else if (WTERMSIG(status) == 2)
		{
			printf("\n");
			return (ERROR);
		}
	}
	return (99);
}

int	pipe_exec(t_tree *tree, t_bash *bash)
{
	int		wait;
	int		status;

	set_variable_pipe_exec(bash, &status);
	exec_tree(tree->left, bash);
	set_variable_pipe_exec(bash, &status);
	exec_tree(tree->right, bash);
	if (check_last_pipe(tree))
		check_last_pipe_utils(bash, &wait, &status);
	if (signals_pipe_exec_utils(status) == ERROR)
		return (ERROR);
	else if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
			return (ERROR);
		return (SUCCESS);
	}
	return (SUCCESS);
}
