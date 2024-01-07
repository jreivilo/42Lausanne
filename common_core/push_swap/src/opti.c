/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opti.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:17:09 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/04 16:44:38 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	opti1(long int *stack_a, long int *stack_b, long int *pos)
{
	if (find_pos(stack_a, stack_b[1]) == 0 && *pos > 3)
	{
		rotate_b(stack_b);
		push_a(stack_a, stack_b);
		while (find_pos(stack_a, stack_b[0]) == 0)
		{
			push_a(stack_a, stack_b);
			*pos = *pos + 1;
		}
		reverse_rotate_b(stack_b);
		*pos = *pos + 1;
	}
	opti12(stack_a, stack_b, pos);
}

void	opti12(long int *stack_a, long int *stack_b, long int *pos)
{
	if (find_pos(stack_a, stack_b[2]) == 0 && *pos > 5)
	{
		rotate_b(stack_b);
		rotate_b(stack_b);
		push_a(stack_a, stack_b);
		while (find_pos(stack_a, stack_b[0]) == 0)
		{
			push_a(stack_a, stack_b);
			*pos = *pos + 1;
		}
		opti1(stack_a, stack_b, pos);
		reverse_rotate_b(stack_b);
		if (find_pos(stack_a, stack_b[0]) == 0)
		{
			push_a(stack_a, stack_b);
			*pos = *pos + 1;
		}
		reverse_rotate_b(stack_b);
		*pos = *pos + 1;
	}
}

void	opti2(long int *stack_a, long int *stack_b, long int *pos)
{
	if (find_pos(stack_a, stack_b[1]) == 0 && len_s(stack_a) - *pos > 3)
	{
		rotate_b(stack_b);
		push_a(stack_a, stack_b);
		*pos = *pos + 1;
		while (find_pos(stack_a, stack_b[0]) == 0)
		{
			push_a(stack_a, stack_b);
			*pos = *pos + 1;
		}
		if (*pos < len_s(stack_a))
			reverse_rotate_r(stack_a, stack_b);
		else
			reverse_rotate_b(stack_b);
		*pos = *pos + 1;
	}
}
