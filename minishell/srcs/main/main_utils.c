/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:27:52 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/14 21:28:05 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_main(t_tree *tree, t_bash *bash)
{
	bash->in_fd = 0;
	bash->out_fd = 1;
	bash->hrdc = 0;
	set_signal(0);
	exec_tree(tree, bash);
	close(bash->tmp_fd);
	free_tree(tree);
	tree = NULL;
}

int	main_special_case(int argc)
{
	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (0);
	}
	return (1);
}

void	main_special_case2(t_bash *bash)
{
	if (!bash->input)
	{
		tty_attribute(0);
		exit(0);
	}
}
