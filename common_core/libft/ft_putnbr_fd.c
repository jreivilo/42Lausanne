/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:33:37 by jolivier          #+#    #+#             */
/*   Updated: 2022/09/15 11:33:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	a;
	int		shift;

	shift = 0;
	if (n < 0)
	{
		write (fd, "-", 1);
		n = n * -1;
	}
	if (n == -2147483648)
	{
		write(fd, "2147483648", 10);
		shift = 1;
	}
	if (n > 9)
	{
		ft_putnbr_fd (n / 10, fd);
	}
	a = n % 10 + '0';
	if (shift != 1)
	{
		write (fd, &a, 1);
	}
}
