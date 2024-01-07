/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:40:37 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/10 18:40:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_a(long int	*stack_a, long int	*stack_b)
{
	long int	i;

	i = 0;
	if (stack_b[0] != '\0')
		stack_top(stack_a, stack_b[0]);
	while (stack_b[i] != '\0')
	{
		stack_b[i] = stack_b[i + 1];
		i++;
	}
	stack_b[i] = '\0';
	write(1, "pa\n", 3);
}

void	push_b(long int	*stack_a, long int	*stack_b)
{
	long int	i;

	i = 0;
	if (stack_a[0] != '\0')
		stack_top(stack_b, stack_a[0]);
	while (stack_a[i] != '\0')
	{
		stack_a[i] = stack_a[i + 1];
		i++;
	}
	stack_a[i] = '\0';
	write(1, "pb\n", 3);
}
