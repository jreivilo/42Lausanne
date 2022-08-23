/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:32:57 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/16 17:33:04 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>

void	ft_rev_int_tab(int *tab, int size)
{
	int	i;
	int	memory;
	int	size_copy;

	size_copy = size;
	i = 0;
	memory = 0;
	while (size / 2 > 0)
	{
		memory = *(tab + i);
		*(tab + i) = *(tab + size_copy - 1);
		*(tab + size_copy - 1) = memory;
		i++;
		size--;
		size--;
		size_copy--;
	}
}
/*
int main()
{
	int p = 1;
	int i = 0;
	int t[] = {1,2,3,4,5};
	ft_rev_int_tab(t, 5);
	for(i=0;i<5;i++)
	{
		printf("%i", t[i]);
	}

}
*/