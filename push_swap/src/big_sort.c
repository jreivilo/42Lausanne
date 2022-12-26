/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:54:07 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/15 12:54:07 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long int	check_in_stack(long int *stack, long int v, long int s, long int e)
{
	long int	i;

	i = s;
	while (i < e)
	{
		if (stack[i] == v)
			return (1);
		i++;
	}
	return (0);
}

void	big_b_to_a(long int *stack_a, long int *stack_b)
{
	long int	pos;

	while (stack_b[0] != '\0')
	{
		pos = find_pos(stack_a, stack_b[0]);
		if (find_pos(stack_a, stack_b[0]) <= len_s(stack_a) / 2)
		{
			while (pos > 0)
			{
				rotate_a(stack_a);
				pos--;
			}
		}
		else
		{
			while (pos < len_s(stack_a))
			{
				reverse_rotate_a(stack_a);
				pos++;
			}
		}
		push_a(stack_a, stack_b);
	}
}

void	rot_minstart_minend(long int *stack_b, long int *start, long int *end)
{
	rotate_b(stack_b);
	*start = *start - 1;
	*end = *end - 1;
}

void	a_to_b(long int *stack_a, long int *stack_b, long int length)
{
	long int	*sort_stack;
	long int	start;
	long int	end;

	sort_stack = malloc(sizeof(long int) * (length + 1));
	ft_memcpy(sort_stack, stack_a, sizeof(long int) * (length + 1));
	sort(sort_stack);
	start_end(&start, &end, length);
	while (len_s(stack_a) > 3)
	{
		start_end_min_max(&start, &end, length);
		while (len_s(stack_a) > 3)
		{
			if (check_in_stack(sort_stack, stack_a[0], start, end) == 1)
			{
				pushb_plusend(stack_a, stack_b, &end);
				if (stack_b[0] < sort_stack[(length / 2)])
					rot_minstart_minend(stack_b, &start, &end);
				start_end_min_max(&start, &end, length);
			}
			else
				rotate_a(stack_a);
		}
	}
	free(sort_stack);
}

void	big_sort(long int *stack_a, long int *stack_b, long int length)
{
	a_to_b(stack_a, stack_b, length);
	small_sort(stack_a, stack_b);
	big_b_to_a(stack_a, stack_b);
	rotate_min_first(stack_a);
}
