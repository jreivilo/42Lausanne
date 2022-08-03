/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 16:15:35 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/30 16:15:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_stock_str.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_strlength(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	str_cpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

struct	s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	int			j;
	t_stock_str	*tab;

	j = 0;
	tab = malloc(sizeof(*tab) * (ac + 1));
	if (tab == NULL)
		return (NULL);
	while (j < ac)
	{
		tab[j].size = ft_strlength(av[j]);
		tab[j].str = av[j];
		tab[j].copy = malloc(sizeof(char) * (ft_strlength(av[j]) + 1));
		if (tab[j].copy == NULL)
			return (NULL);
		str_cpy(tab[j].copy, av[j]);
		j++;
	}
	tab[j].size = 0;
	tab[j].str = 0;
	tab[j].copy = 0;
	return (tab);
}
/*
int	main(int ac, char **av)
{
	printf("%s\n", ft_strs_to_tab(ac, av)[0].str);
	printf("%s\n", ft_strs_to_tab(ac, av)[0].copy);
	printf("%i\n", ft_strs_to_tab(ac, av)[0].size);
}
*/