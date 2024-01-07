/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:08:29 by jolivier          #+#    #+#             */
/*   Updated: 2022/09/05 11:08:29 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (c > 255)
		c = c % 256;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == c)
		return ((char *)str + i);
	return ((void *)0);
}
/*
int main()
{
	char *str = "s";
	int i = 's' + 256;
	char *ptr = ft_strchr(str, 's' + 256);
	printf("%i", i);
	printf("%s", ptr);
	return (0);
}
*/