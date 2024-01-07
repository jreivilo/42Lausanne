/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:05:47 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/13 15:06:04 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_double_left_signal(t_tree *tree, t_bash *bash, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			printf("\n");
			exec_tree(tree->left, bash);
		}
	}
	else if (WIFEXITED(status))
	{
		if (status)
			return (ERROR);
		return (exec_tree(tree->left, bash));
	}
	return (exec_tree(tree->left, bash));
}
