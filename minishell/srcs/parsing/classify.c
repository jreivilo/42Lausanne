/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:25:06 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 19:06:29 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tolower_str(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		(*str)[i] = (char) ft_tolower((*str)[i]);
		i++;
	}
}

int	is_builtin(char *cmd)
{
	ft_tolower_str(&cmd);
	if (ft_strcmp(cmd, "cd") == 0)
		return (2);
	if (ft_strcmp(cmd, "echo") == 0)
		return (4);
	if (ft_strcmp(cmd, "env") == 0)
		return (3);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (6);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (3);
	if (ft_strcmp(cmd, "unset") == 0)
		return (5);
	return (0);
}

void	free_token_double_redir(char **word)
{
	if (word[0][0] == '<' && word[0][1] == '<')
	{
		free(word[0]);
		free(word);
	}
	if (word[0][0] == '>' && word[0][1] == '>')
	{
		free(word[0]);
		free(word);
	}
}

void	free_token(char **word, char *path)
{
	if (path)
		free(path);
	if (word[0][0] == '|')
	{
		free(word[0]);
		free(word);
	}
	if (word[0][0] == '>')
	{
		free(word[0]);
		free(word);
	}
	if (word[0][0] == '<')
	{
		free(word[0]);
		free(word);
	}
	free_token_double_redir(word);
}

void	classify(t_tree *tree, char **env)
{
	char		*tmp;
	char		*path;
	char		**word;
	t_file		*type_file;

	tmp = swap_var2(tree->input, env);
	word = ft_split_parse2(tmp, 32);
	free(tmp);
	path = get_path_cmd(word[0], env);
	if (is_builtin(word[0]))
		buildset(&tree, word);
	else if (path)
		pathset(&tree, word);
	else if (open(word[0], O_RDONLY) != -1)
	{
		type_file = malloc(sizeof(t_file));
		type_file->file = word[0];
		tree->type = type_file;
		tree->token = FILES;
	}
	else
		tokset(&tree, word);
	free_token(word, path);
}
