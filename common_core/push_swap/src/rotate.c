/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:40:13 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/10 18:40:13 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_a(long int	*stack_a)
{
	long int	i;
	long int	tmp;

	i = 0;
	tmp = stack_a[0];
	while (stack_a[i] != '\0')
	{
		stack_a[i] = stack_a[i + 1];
		i++;
	}
	stack_a[i - 1] = tmp;
	write(1, "ra\n", 3);
}

void	rotate_b(long int	*stack_b)
{
	long int	i;
	long int	tmp;

	i = 0;
	tmp = stack_b[0];
	while (stack_b[i] != '\0')
	{
		stack_b[i] = stack_b[i + 1];
		i++;
	}
	stack_b[i - 1] = tmp;
	write(1, "rb\n", 3);
}

void	rotate_r(long int	*stack_a, long int	*stack_b)
{
	rotate_a(stack_a);
	rotate_b(stack_b);
}
