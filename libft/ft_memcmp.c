/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 08:47:37 by jolivier          #+#    #+#             */
/*   Updated: 2022/08/23 08:47:37 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (((unsigned char *)str1)[i] == ((unsigned char *)str2)[i] && i < n)
	{
		i++;
	}
	if (i == n)
	{
		i = i - 1;
		return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
	}
	return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
}
