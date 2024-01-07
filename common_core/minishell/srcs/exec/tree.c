/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:28:36 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/14 17:58:07 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_tree_other_token(t_tree *tree, t_bash *bash)
{
	if (tree->token == PIPE)
		return (pipe_exec(tree, bash));
	else if (tree->token == APPEND)
		return (redir_double_right(tree, bash));
	else if (tree->token == HR_DC)
		return (redir_double_left(tree, bash));
	else if (tree->token == OUT_FILE)
		return (redir_right(tree, bash));
	else if (tree->token == IN_FILE)
		return (redir_left(tree, bash));
	return (SUCCESS);
}

int	exec_tree_pipe_and(t_tree *tree, t_bash *bash)
{
	if (tree->token == AND)
	{
		if (exec_tree(tree->left, bash) == SUCCESS)
		{
			bash->tmp_fd = dup(STDIN_FILENO);
			return (exec_tree(tree->right, bash));
		}
	}
	else if (tree->token == OR)
	{
		if (exec_tree(tree->left, bash) == ERROR)
		{
			bash->tmp_fd = dup(STDIN_FILENO);
			return (exec_tree(tree->right, bash));
		}
	}
	return (SUCCESS);
}

int	exec_tree(t_tree *tree, t_bash *bash)
{
	if (tree == NULL)
		return (SUCCESS);
	classify(tree, bash->env);
	if (tree->token == CMD || tree->token == BUILT_IN)
		return (start_exec(tree, bash));
	if (tree->token == NOPE)
	{
		ft_putstr_fd("not_bash: ", 2);
		ft_putstr_fd(((t_error *)tree->type)->cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("command not found\n", 2);
		g_status = 127;
		return (ERROR);
	}
	else if (tree->token == AND || tree->token == OR)
		return (exec_tree_pipe_and(tree, bash));
	else
		return (exec_tree_other_token(tree, bash));
	return (SUCCESS);
}
