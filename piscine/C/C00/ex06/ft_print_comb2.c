/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 16:36:59 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/14 16:50:41 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	pr1(int a, int b)
{
	char	c1;
	char	c2;
	char	d1;
	char	d2;

	c1 = (a / 10) + '0';
	c2 = a - (a / 10 * 10) + '0';
	d1 = (b / 10) + '0';
	d2 = b - (b / 10 * 10) + '0';
	write (1, &c1, 1);
	write (1, &c2, 1);
	write (1, " ", 1);
	write (1, &d1, 1);
	write (1, &d2, 1);
	if (a != 98 | b != 99)
	{
		write (1, ", ", 2);
	}
}

void	ft_print_comb2(void)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (a <= 97)
	{
		if (b == 99)
		{
			pr1(a, b);
			++a;
			b = a + 1;
		}
		pr1(a, b);
		++b;
	}
}
/*
int main()
{
	ft_print_comb2();
}
*/