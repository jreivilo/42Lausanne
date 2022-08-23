/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:26:31 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/26 15:26:32 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	*ft_range(int min, int max)
{
	int	i;
	int	size;
	int	*tab;

	i = 0;
	size = 0;
	if (min >= max)
		return ((void *)0);
		size = max - min;
	tab = malloc(sizeof(*tab) * (size));
	if (tab != (void *)0)
	{
		while (min < max)
		{
			tab[i] = min;
			i++;
			min++;
		}
	}
	return (tab);
}
/*
int main()
{
	printf("%d", ft_range(1 , 4)[0]);
	printf("%d", ft_range(1 , 4)[1]);
	printf("%d\n", ft_range(1 , 4)[2]);
	return(0);
}
*/