/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:45:40 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/14 14:09:22 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	pr(char a, char b, char c)
{
	write (1, &a, 1);
	write (1, &b, 1);
	write (1, &c, 1);
	if (a <= '6')
	{
		write (1, ", ", 2);
	}
}

void	ft_print_comb(void)
{
	char	a;
	char	b;
	char	c;

	a = '0';
	b = '1';
	c = '2';
	while (a <= '6')
	{
		if (b == '8')
		{
			++a;
			b = a + 1;
			c = b + 1;
		}
		if (c == '9' & a <= '6')
		{
			pr(a, b, c);
			++b;
			c = b + 1;
		}
		pr(a, b, c);
		++c;
	}
}
