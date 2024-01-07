/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:16:47 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/13 08:16:47 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void count_pipe(t_tree *tree, t_bash *bash)
{
	if (!ft_strncmp(tree->input, "|", 1))
		bash->pipe++;
	if (tree->left)
		count_pipe(tree->left, bash);
	if (tree->right)
		count_pipe(tree->right, bash);
}*/

void	get_line(char **input)
{
	*input = readline("not_bash$ ");
	add_history(*input);
}

void	init_bash(t_bash *bash, char **envp)
{
	bash->pid = 0;
	bash->env = ft_tabdup(envp);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

int	main(int argc, char **argv, char **envp)
{
	t_tree	*tree;
	t_bash	bash;

	(void)argv;
	init_bash(&bash, envp);
	if (main_special_case(argc) == 0)
		return (0);
	while (1)
	{
		bash.tmp_fd = dup(STDIN_FILENO);
		tty_attribute(1);
		set_signal(1);
		get_line(&bash.input);
		main_special_case2(&bash);
		if (is_empty(bash.input))
		{
			free(bash.input);
			continue ;
		}
		if (*bash.input)
			tree = create_tree(bash.input, NULL);
		if (tree)
			tree_main(tree, &bash);
	}
	return (0);
}
