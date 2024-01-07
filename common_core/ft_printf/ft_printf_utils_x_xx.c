/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_x_xx.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:59:26 by jolivier          #+#    #+#             */
/*   Updated: 2022/10/19 17:59:29 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_count_x(unsigned int n)
{
	ft_putnbr_x(n);
	return (count_number_x(n));
}

int	count_number_x(unsigned int n)
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

void	ft_putnbr_x(unsigned int n)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (n > 15)
	{
		ft_putnbr_x(n / 16);
	}
	write(1, &hexa[n % 16], 1);
}

int	ft_putnbr_count_xx(unsigned int n)
{
	ft_putnbr_xx(n);
	return (count_number_x(n));
}

void	ft_putnbr_xx(unsigned int n)
{
	char	*hexa;

	hexa = "0123456789ABCDEF";
	if (n > 15)
	{
		ft_putnbr_xx(n / 16);
	}
	write(1, &hexa[n % 16], 1);
}
