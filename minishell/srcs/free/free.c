/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:39:59 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 18:21:48 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

void	free_buitins_and_cmd(t_tree *tree)
{
	if (tree->token == BUILT_IN)
	{
		free_tab(((t_builtin *)tree->type)->args);
		free(tree->type);
	}
	if (tree->token == CMD)
	{
		free_tab(((t_cmd *)tree->type)->args);
		free(tree->type);
	}
}

void	free_tree(t_tree *tree)
{
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	free_buitins_and_cmd(tree);
	if (tree->token == FILES)
	{
		free(((t_file *)tree->type)->file);
		free(tree->type);
	}
	if (tree->token == PIPE)
		free(tree->type);
	if (tree->token == NOPE)
	{
		free_tab(((t_error *)tree->type)->args);
		free(tree->type);
	}
	free(tree->input);
	free(tree);
}
