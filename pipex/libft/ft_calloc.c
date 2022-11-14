/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:11:20 by jolivier          #+#    #+#             */
/*   Updated: 2022/08/24 10:11:20 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize )
{
	void	*ptr;
	size_t	i;

	ptr = malloc(elementCount * elementSize);
	if (ptr != (void *)0)
	{
		i = 0;
		while (i < (elementCount * elementSize))
		{
			((char *)ptr)[i] = 0;
			i++;
		}
	}
	return (ptr);
}
