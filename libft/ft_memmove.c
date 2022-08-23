/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 23:20:57 by jolivier          #+#    #+#             */
/*   Updated: 2022/08/19 23:20:57 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (str1 < str2)
	{
		while (i < n)
		{
			((unsigned char *)str1)[i] = ((unsigned char *)str2)[i];
			i++;
		}
		return (str1);
	}
	while (i < n)
	{
		((unsigned char *)str1)[n - i - 1] = ((unsigned char *)str2)[n - i - 1];
		i++;
	}
	return (str1);
}
