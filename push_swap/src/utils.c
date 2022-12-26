/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:22:29 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/26 18:15:43 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long int	len_s(long int *stack)
{
	long int	i;

	i = 0;
	while (stack[i] != 0)
		i++;
	return (i);
}

long int	find_min(long int *stack)
{
	long int	i;
	long int	min;

	i = 0;
	min = stack[0];
	while (stack[i] != '\0')
	{
		if (stack[i] < min)
			min = stack[i];
		i++;
	}
	return (min);
}

long int	find_max(long int *stack)
{
	long int	i;
	long int	max;

	i = 0;
	max = stack[0];
	while (stack[i] != '\0')
	{
		if (stack[i] > max)
			max = stack[i];
		i++;
	}
	return (max);
}

void	rotate_min_first(long int *stack)
{
	while (stack[0] != find_min(stack))
	{
		if (find_pos_on(stack, find_min(stack)) > len_s(stack) / 2)
			reverse_rotate_a(stack);
		else
			rotate_a(stack);
	}
}
