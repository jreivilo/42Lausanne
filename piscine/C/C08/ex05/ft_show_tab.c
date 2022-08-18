/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:19:48 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/31 13:19:50 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, str + i, 1);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	char	a;
	int		shift;

	shift = 0;
	if (nb < 0)
	{
		write (1, "-", 1);
		nb = nb * -1;
	}
	if (nb > 9)
	{
		ft_putnbr (nb / 10);
	}
	if (nb == -2147483648)
	{
		write(1, "2147483648", 10);
		shift = 1;
	}
	a = nb % 10 + '0';
	if (shift != 1)
	{
		write (1, &a, 1);
	}
}

void	ft_show_tab(struct s_stock_str *par)
{
	int	i;

	i = 0;
	while (par[i].str != 0)
	{
		ft_putstr(par[i].str);
		write(1, "\n", 1);
		ft_putnbr(par[i].size);
		write(1, "\n", 1);
		ft_putstr(par[i].copy);
		write(1, "\n", 1);
		i++;
	}
}

/*
int	main(int ac, char **av)
{
	ft_show_tab(ft_strs_to_tab(ac, av));
}
*/