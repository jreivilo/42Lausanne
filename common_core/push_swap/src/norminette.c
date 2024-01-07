/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:44:47 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/25 11:44:47 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	start_end_min_max(long int *start, long int *end, long int length)
{
	if (*start < 0)
		*start = 0;
	if (*end > length - 3)
		*end = length - 3;
}

void	start_end(long int *start, long int *end, long int length)
{
	*start = (length / 2) - (length / get_n(length));
	*end = (length / 2) + (length / get_n(length));
}

long int	get_n(long int length)
{
	if (length < 11)
		return (5);
	if (length < 101 && length >= 11)
		return (12);
	else
		return (33);
}

void	pushb_plusend(long int *stack_a, long int *stack_b, long int *end)
{
	push_b(stack_a, stack_b);
	*end = *end + 1;
}
