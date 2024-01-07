/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:56:18 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/26 18:15:35 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_sort(long int *st_a, long int *st_b)
{
	(void)st_b;
	if (st_a[0] > st_a[1] && st_a[1] < st_a[2] && st_a[0] < st_a[2])
		swap_a(st_a);
	if (st_a[0] > st_a[1] && st_a[1] > st_a[2] && st_a[0] > st_a[2])
	{
		swap_a(st_a);
		reverse_rotate_a(st_a);
	}
	if (st_a[0] > st_a[1] && st_a[1] < st_a[2] && st_a[0] > st_a[2])
		rotate_a(st_a);
	if (st_a[0] < st_a[1] && st_a[1] > st_a[2] && st_a[0] < st_a[2])
	{
		swap_a(st_a);
		rotate_a(st_a);
	}
	if (st_a[0] < st_a[1] && st_a[1] > st_a[2] && st_a[0] > st_a[2])
		reverse_rotate_a(st_a);
}
