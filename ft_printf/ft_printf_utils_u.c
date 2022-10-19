/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:53:39 by jolivier          #+#    #+#             */
/*   Updated: 2022/10/19 17:54:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_count_u(unsigned int n)
{
	ft_putnbr_u(n);
	return (count_number_u(n));
}

int	count_number_u(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	ft_putnbr_u(unsigned int n)
{
	char	a;
	int		shift;
	int		len;

	len = 0;
	shift = 0;
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
