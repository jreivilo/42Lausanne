/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_i_d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:51:41 by jolivier          #+#    #+#             */
/*   Updated: 2022/10/19 18:02:38 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_count(int n)
{
	ft_putnbr(n);
	return (count_number(n));
}

int	count_number(int n)
{
	int	count;

	count = 0;
	if (-2147483648 == n)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	ft_putnbr(int n)
{
	char	a;
	int		shift;
	int		len;

	len = 0;
	shift = 0;
	if (n < 0)
	{
		write (1, "-", 1);
		n = n * -1;
	}
	if (n == -2147483648)
	{
		write(1, "2147483648", 10);
		shift = 1;
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
	}
	a = n % 10 + '0';
	if (shift != 1)
	{
		write (1, &a, 1);
	}
}
