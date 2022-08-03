/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 12:29:26 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/25 12:29:27 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_sqrt(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		return (0);
	while ((i * i) != nb && i <= 47000)
	{
		i++;
	}
	if (nb / i == i)
		return (i);
	return (0);
}
/*
int main()
{
	printf("%i\n", ft_sqrt(1041500557));
	return(0);
}
*/