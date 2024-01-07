/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:43:00 by jolivier          #+#    #+#             */
/*   Updated: 2022/08/24 10:43:00 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int		i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_add_to_dest(char *dest, int sign, int size, int i)
{
	dest[size] = '\0';
	size--;
	while (-sign <= size)
	{
		dest[size] = (i % 10) + '0';
		size--;
		i = i / 10;
	}
	if (sign == -1)
		dest[0] = '-';
	return (dest);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*dest;
	int		sign;

	size = 0;
	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		sign = -1;
		n = -n;
		size++;
	}
	size = size + ft_count_digits(n);
	dest = malloc(sizeof(char) * (size + 1));
	if (dest != (void *)0)
		ft_add_to_dest(dest, sign, size, n);
	return (dest);
}
