/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:17:34 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/17 19:17:36 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_putchar(char c);

void	start(char count, char c)
{
	ft_putchar('A');
	while (count > 2)
	{
		ft_putchar('B');
		count--;
	}
	if (c > 1)
	{
		ft_putchar('C');
	}
	ft_putchar('\n');
}

void	mid(char r, char count, char c)
{
	while (r > 2)
	{
		ft_putchar('B');
		while (count > 2)
		{
			ft_putchar(' ');
			count--;
		}
		count = c;
		if (c > 1)
		{
			ft_putchar('B');
		}
		ft_putchar('\n');
		r--;
	}
}

void	end(char r, char count, char c)
{
	if (r > 1)
	{
		ft_putchar('A');
		while (count > 2)
		{
			ft_putchar('B');
			count--;
		}
		if (c > 1)
		{
			ft_putchar('C');
		}
		ft_putchar('\n');
	}
}

void	rush(int x, int y)
{
	if (x > 0 && y > 0)
	{
		start(x, x);
		mid(y, x, x);
		end(y, x, x);
	}
}
