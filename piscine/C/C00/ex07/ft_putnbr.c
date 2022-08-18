/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:40:55 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/15 12:53:57 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

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
/*
int main()
{
	ft_putnbr(-2147483648);
}
*/