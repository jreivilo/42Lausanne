/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:59:17 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/26 18:15:18 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long int	norminette_find_pos(long int *stack_a, long int stack)
{
	long int	i;

	i = 0;
	if (stack > find_max(stack_a))
	{
		i = 0;
		while (stack_a[i] != '\0')
		{
			if (stack_a[i] == find_max(stack_a))
				return (i + 1);
			i++;
		}
	}
	if (stack < find_min(stack_a))
	{
		i = 0;
		while (stack_a[i] != '\0')
		{
			if (stack_a[i] == find_min(stack_a))
				return (i);
			i++;
		}
	}
	return (-1);
}

long int	find_pos(long int *stack_a, long int stack)
{
	long int	i;

	i = 0;
	if (norminette_find_pos(stack_a, stack) != -1)
		return (norminette_find_pos(stack_a, stack));
	while (stack_a[i] != '\0')
	{
		if (i == 0)
		{
			if (stack < stack_a[i] && stack > stack_a[len_s(stack_a) - 1])
				return (i);
		}
		if (stack < stack_a[i] && stack > stack_a[i - 1] && i != 0)
			return (i);
		i++;
	}
	return (-1);
}

long int	find_pos_on(long int *stack_a, long int stack)
{
	long int	i;

	i = 0;
	while (stack_a[i] != '\0')
	{
		if (stack_a[i] == stack)
			return (i);
		i++;
	}
	return (-1);
}

void	b_to_a(long int *st_a, long int *st_b)
{
	while (st_b[0] != '\0')
	{
		if (st_b[0] < st_a[0] && st_b[0] > (st_a[len_s(st_a) - 1]))
			push_a(st_a, st_b);
		if (st_a[0] == find_min(st_a) && st_b[0] < find_min(st_a))
			push_a(st_a, st_b);
		if (st_a[len_s(st_a) - 1] == find_max(st_a) && st_b[0] > find_max(st_a))
			push_a(st_a, st_b);
		if (st_b[0] != '\0')
		{
			if (find_pos(st_a, st_b[0]) > len_s(st_a) / 2)
				reverse_rotate_a(st_a);
			else
				rotate_a(st_a);
		}
	}
}

void	medium_sort(long int *st_a, long int *st_b, long int length)
{
	while (length > 3)
	{
		push_b(st_a, st_b);
		length--;
	}
	small_sort(st_a, st_b);
	b_to_a(st_a, st_b);
	while (st_a[0] != find_min(st_a))
	{
		if (find_pos_on(st_a, find_min(st_a)) > len_s(st_a) / 2)
			reverse_rotate_a(st_a);
		else
			rotate_a(st_a);
	}
}
