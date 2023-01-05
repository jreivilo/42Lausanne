/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:08:07 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/04 19:14:05 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

void	free_all(long int *stack_a, long int *stack_b, char **argv)
{
	free(stack_a);
	free(stack_b);
	free_tab(argv);
}
