/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:00:06 by jolivier          #+#    #+#             */
/*   Updated: 2022/10/19 18:01:03 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_count_p(unsigned long n)
{
	write(1, "0x", 2);
	if (!n)
	{
		write(1, "0", 1);
		return (3);
	}
	ft_putnbr_p(n);
	return (count_number_p(n) + 2);
}

int	count_number_p(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

void	ft_putnbr_p(unsigned long n)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (n > 15)
	{
		ft_putnbr_p(n / 16);
	}
	write(1, &hexa[n % 16], 1);
}
