/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:20:14 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/26 16:20:15 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (min >= max)
	{
		*range = NULL;
		return (0);
	}
	size = max - min;
	*range = malloc(sizeof(int) * (size));
	if (*range != (void *)0)
	{
		while (min < max)
		{
			(*range)[i] = min;
			i++;
			min++;
		}
	}
	if (*range == (void *)0)
		return (-1);
	return (size);
}
/*
int main()
{
	int **tab;
	printf("%d\n", ft_ultimate_range(tab, 1 , 4));
	printf("%d", *tab[0]);
	return(0);
}
*/