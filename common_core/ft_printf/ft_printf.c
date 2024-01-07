/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:17:05 by jolivier          #+#    #+#             */
/*   Updated: 2022/10/19 18:02:59 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdlib.h>

int	ft_check_type(const char format, va_list *arg)
{
	int	len;

	len = 0;
	if (format == '%')
		return (ft_putchar('%'));
	if (format == 'c')
		len = ft_putchar(va_arg(*arg, int));
	if (format == 's')
		len = ft_putstr(va_arg(*arg, char *));
	if (format == 'p')
		len = ft_putnbr_count_p(va_arg(*arg, unsigned long));
	if (format == 'd' || format == 'i')
		len = ft_putnbr_count(va_arg(*arg, int));
	if (format == 'u')
		len = ft_putnbr_count_u(va_arg(*arg, unsigned int));
	if (format == 'x')
		len = ft_putnbr_count_x(va_arg(*arg, unsigned int));
	if (format == 'X')
		len = ft_putnbr_count_xx(va_arg(*arg, unsigned int));
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += ft_check_type(format[i], &arg);
		}
		else
		{
			write(1, &format[i], 1);
			len++;
		}
		i++;
	}
	va_end(arg);
	return (len);
}
