/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:40:32 by afrigger          #+#    #+#             */
/*   Updated: 2023/03/14 18:01:59 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pathset(t_tree **tmp, char **word)
{
	t_cmd	*type_cmd;
	t_tree	*tree;

	tree = *tmp;
	type_cmd = malloc(sizeof(t_cmd));
	type_cmd->cmd = word[0];
	type_cmd->args = word;
	tree->type = type_cmd;
	tree->token = CMD;
}

void	buildset(t_tree **tmp, char **word)
{
	t_builtin	*type_built;
	t_tree		*tree;

	tree = *tmp;
	type_built = malloc(sizeof(t_builtin));
	type_built->cmd = word[0];
	type_built->args = word;
	tree->type = type_built;
	tree->token = BUILT_IN;
}

void	tokset(t_tree **tmp, char **word)
{
	t_tree	*tree;

	tree = *tmp;
	if (ft_strncmp(word[0], "&&", 2) == 0)
		tree->token = AND;
	else if (ft_strncmp(word[0], "||", 2) == 0)
		tree->token = OR;
	else if (ft_strncmp(word[0], "|", 1) == 0)
		tree->token = PIPE;
	else if (ft_strncmp(word[0], "<<", 2) == 0)
		tree->token = HR_DC;
	else if (ft_strncmp(word[0], ">>", 2) == 0)
		tree->token = APPEND;
	else if (ft_strncmp(word[0], ">", 1) == 0)
		tree->token = OUT_FILE;
	else if (ft_strncmp(word[0], "<", 1) == 0)
		tree->token = IN_FILE;
	else
		errset(&tree, word);
}

void	errset(t_tree **tmp, char **word)
{
	t_tree	*tree;
	t_error	*type_error;

	tree = *tmp;
	tree->token = NOPE;
	type_error = malloc(sizeof(t_file));
	type_error->cmd = word[0];
	type_error->args = word;
	tree->type = type_error;
}
