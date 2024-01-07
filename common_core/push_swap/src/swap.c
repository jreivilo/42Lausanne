/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:43:26 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/10 18:43:26 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_a(long int	*stack_a)
{
	long long int	tmp;

	if (stack_a[0] != 0 && stack_a[1] != 0)
	{
		tmp = stack_a[0];
		stack_a[0] = stack_a[1];
		stack_a[1] = tmp;
	}
	write(1, "sa\n", 3);
}

void	swap_b(long int	*stack_b)
{
	long long int	tmp;

	if (stack_b[0] != 0 && stack_b[1] != 0)
	{
		tmp = stack_b[0];
		stack_b[0] = stack_b[1];
		stack_b[1] = tmp;
	}
	write(1, "sb\n", 3);
}

void	swap_s(long int	*stack_a, long int	*stack_b)
{
	swap_a(stack_a);
	swap_b(stack_b);
}
