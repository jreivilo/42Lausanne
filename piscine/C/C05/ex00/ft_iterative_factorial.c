/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 19:55:12 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/21 19:55:42 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_iterative_factorial(int nb)
{
	int	n;

	n = nb;
	if (nb < 0)
	{
		return (0);
	}
	if (nb == 1 || nb == 0)
	{
		return (1);
	}
	while (nb > 1)
	{
		n = n * (nb - 1);
		nb--;
	}
	return (n);
}
/*
int main()
{
	printf("RES:%i\n", ft_iterative_factorial(4));
}
*/