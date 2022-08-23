/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:56:01 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/25 16:56:03 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_is_prime(int nb)
{
	int	i;

	i = 3;
	if (nb == 2)
	{
		return (1);
	}
	while (nb % i != 0 && i < nb)
	{
		i = i + 2;
	}
	if (i == nb)
	{
		return (1);
	}
	return (0);
}
/*
int main ()
{
	printf("%i\n", ft_is_prime(25));
}
*/