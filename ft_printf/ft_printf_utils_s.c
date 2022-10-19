/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:50:49 by jolivier          #+#    #+#             */
/*   Updated: 2022/10/19 18:11:50 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}
