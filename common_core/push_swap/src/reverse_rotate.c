/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:44:45 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/10 18:44:45 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate_a(long int	*stack_a)
{
	long int	i;
	long int	tmp;

	i = 0;
	while (stack_a[i] != '\0')
	{
		i++;
	}
	tmp = stack_a[i - 1];
	stack_a[i - 1] = '\0';
	while (i > 0)
	{
		stack_a[i] = stack_a[i - 1];
		i--;
	}
	stack_a[0] = tmp;
	write(1, "rra\n", 4);
}

void	reverse_rotate_b(long int	*stack_b)
{
	long int	i;
	long int	tmp;

	i = 0;
	while (stack_b[i] != '\0')
	{
		i++;
	}
	tmp = stack_b[i - 1];
	stack_b[i - 1] = '\0';
	while (i > 0)
	{
		stack_b[i] = stack_b[i - 1];
		i--;
	}
	stack_b[0] = tmp;
	write(1, "rrb\n", 4);
}

void	reverse_rotate_r(long int	*stack_a, long int	*stack_b)
{
	reverse_rotate_a(stack_a);
	reverse_rotate_b(stack_b);
}
